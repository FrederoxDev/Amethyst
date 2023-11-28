#include "amethyst/Memory.h"
#include <thread>
#include <mutex>


uintptr_t GetMinecraftBaseAddress() {
	static uintptr_t mc = reinterpret_cast<uintptr_t>(GetModuleHandleA("Minecraft.Windows.exe"));
	return mc;
}

unsigned long GetMinecraftSize() {
	HMODULE base = GetModuleHandleA("Minecraft.Windows.exe");
	if (base == nullptr) return 0;

	MODULEINFO moduleInfo;
	if (!GetModuleInformation(GetCurrentProcess(), base, &moduleInfo, sizeof(MODULEINFO))) return 0;

	return moduleInfo.SizeOfImage;
}

uintptr_t SlideAddress(uintptr_t offset) {
	return GetMinecraftBaseAddress() + offset;
}

void GenerateSigscanMask(std::string& signature, std::vector<bool>& wildcardMask, std::vector<byte>& bytes) {
	for (size_t i = 0; i < signature.size(); ++i) {
		char c1 = signature[i];
		if (c1 == ' ') continue;

		// Wildcards
		if (c1 == '?') {
			wildcardMask.push_back(true);
			continue;
		}

		wildcardMask.push_back(false);
		char c2 = signature[++i];

		std::string hexString(1, c1);
		hexString += c2;

		bytes.push_back((byte)std::stoi(hexString, nullptr, 16));
	}
}

uintptr_t SigScan(std::string signature) {
	std::vector<bool> wildcardMask;
	std::vector<byte> bytes;

	GenerateSigscanMask(signature, wildcardMask, bytes);

	auto start_time = std::chrono::high_resolution_clock::now();
	uintptr_t base = GetMinecraftBaseAddress();
	uintptr_t size = GetMinecraftSize();


	// Brute force algorithm
	for (uintptr_t address = base; address < base + size; address++) {
		bool failed = false;
		size_t byteIndex = 0;

		for (size_t offset = 0; offset < wildcardMask.size(); offset++) {
			if (wildcardMask[offset]) continue;

			byte expectedByte = bytes[byteIndex++];
			byte realByte = *reinterpret_cast<byte*>(address + offset);

			if (expectedByte != realByte) {
				failed = true;
				break;
			}
		}

		if (failed) continue;
		return address;
	}

	Log::Error("Sigscan failed! {:s}\n", signature);
	throw std::exception();
}

uintptr_t multiThreadedSigScan(
	const std::string* sig,
	const std::vector<bool>& mask
)
{
	uint64_t start = GetMinecraftBaseAddress();
	uint64_t end = start + GetMinecraftSize();

	unsigned int threadCount = std::thread::hardware_concurrency() - 1;
	// leave one thread for the main thread
	uint64_t chunkSize = (end - start) / threadCount;

	std::vector<std::thread> threads;
	std::mutex mutex;
	uint64_t result = 0;
	auto sigScan = [&](uint64_t start, uint64_t end) -> uint64_t{
		for (uint64_t address = start; address < end; address++) {
			if (result != 0) return; // another thread found it
			bool failed = false;
			size_t byteIndex = 0;

			for (size_t offset = 0; offset < mask.size(); offset++) {
				if (mask[offset]) continue;

				byte expectedByte = sig->at(byteIndex++);
				byte realByte = *reinterpret_cast<byte*>(address + offset);

				if (expectedByte != realByte) {
					failed = true;
					break;
				}
			}

			if (failed) continue;

			mutex.lock();
			Log::Info("Found sigscan match at 0x{:X}\n", address);
			result = address;
			mutex.unlock();
			return address;
		}

		return (uint64_t)0;
	};

	for (unsigned int i = 0; i < threadCount; i++) {
		uint64_t threadStart = start + (i * chunkSize);
		uint64_t threadEnd = (i == threadCount - 1) ? end : threadStart + chunkSize;

		threads.emplace_back(std::thread(sigScan, threadStart, threadEnd));
	}

	for (auto& thread : threads) {
		thread.join();
	}

	if (result == 0) {
		Log::Error("Sigscan failed! {:s}\n", *sig);
		return -1;
	}
	else {
		return result;
	}
}