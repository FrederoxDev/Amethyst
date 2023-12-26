#
# Converts a list of already found functions on the client to a json format
# AmethystAPI/KnownFunctionDumper
#
import idautils
import idc
import idaapi
import json
import os

amethyst_folder = os.environ.get("appdata") + "/Amethyst/tools/"

if not os.path.exists(amethyst_folder):
    os.makedirs(amethyst_folder)

known_funcs = []

for function_ea in idautils.Functions():
    # Try demangle the function name, if it works its probably been dumped?
    found_function_name: str = idc.get_func_name(function_ea)
    demangled_name: str = idaapi.demangle_name(found_function_name, 0)

    # Probably hasn't been dumped
    if demangled_name == None:
        continue

    known_funcs.append(found_function_name)

# Dump results into local file
with open(amethyst_folder + "known_funcs.json", "w") as file_handle:
    file_handle.write(json.dumps(known_funcs))

    print(f"Found {len(known_funcs)} functions, dumping to {os.path.abspath(file_handle.name)}")