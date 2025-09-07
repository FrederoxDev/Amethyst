import { readJson, writeJson } from "https://deno.land/x/jsonc@1.1.0/mod.ts";
import { resolve, dirname } from "https://deno.land/std@0.106.0/path/mod.ts";

// Set up Git user for the commit
const gitUserName = "github-actions[bot]";
const gitUserEmail = "github-actions[bot]@users.noreply.github.com";

try {
    const process = Deno.run({
        cmd: ["git", "config", "--global", "user.name", gitUserName],
    });
    await process.status();

    const process2 = Deno.run({
        cmd: ["git", "config", "--global", "user.email", gitUserEmail],
    });
    await process2.status();

    // Deno script to bump the version in mod.json and push the changes
    const filePath = resolve(dirname(import.meta.url), "../..", "mod.json");
    const mod = await readJson(filePath);

    if (mod.version && Array.isArray(mod.version)) {
        mod.version[2] += 1; // Increment the patch version
    } else {
        console.error("Version array not found or invalid in mod.json");
        Deno.exit(1);
    }

    await writeJson(filePath, mod, { spaces: 2 });
    console.log("Updated mod.json with new version");

    // Check for changes and commit
    const changesProcess = Deno.run({
        cmd: ["git", "status", "--porcelain"],
        stdout: "piped",
    });

    const output = await changesProcess.output();
    const changes = new TextDecoder().decode(output).trim();

    if (changes) {
        const addProcess = Deno.run({ cmd: ["git", "add", "mod.json"] });
        await addProcess.status();

        const commitProcess = Deno.run({
            cmd: ["git", "commit", "-m", "Build: Bump version for next build"],
        });
        await commitProcess.status();

        const pushProcess = Deno.run({ cmd: ["git", "push"] });
        await pushProcess.status();

        console.log("Committed and pushed version changes");
    } else {
        console.log("No changes to commit");
    }
} catch (error) {
    console.error(`An error occurred: ${error.message}`);
    Deno.exit(1);
}
