const filePath = "mod.json";
const text = await Deno.readTextFile(filePath);
const mod = JSON.parse(text);

if (mod.meta && mod.meta.version) {
  const versionParts = mod.meta.version.split('.');
  const major = parseInt(versionParts[0]);
  const minor = parseInt(versionParts[1]);
  const patch = parseInt(versionParts[2]) + 1;
  
  mod.meta.version = `${major}.${minor}.${patch}`;
  
  await Deno.writeTextFile(filePath, JSON.stringify(mod, null, 2));
  console.log(`${major}.${minor}.${patch}`);
} else {
  console.error("Version not found in mod.json");
  Deno.exit(1);
}
