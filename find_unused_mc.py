import os, re

root = 'AmethystAPI/src'
src_root = 'src'

# Collect all mc/ header files
mc_files = set()
for dirpath, dirs, files in os.walk(os.path.join(root, 'mc')):
    for f in files:
        if f.endswith(('.hpp', '.h', '.cpp')):
            mc_files.add(os.path.join(dirpath, f).replace(os.sep, '/'))

# Collect all non-mc source files (amethyst/, amethyst-deps/, and src/)
source_files = set()
for dirpath, dirs, files in os.walk(root):
    norm = dirpath.replace(os.sep, '/')
    if '/mc/' in norm or norm.endswith('/mc'):
        continue
    for f in files:
        if f.endswith(('.hpp', '.h', '.cpp')):
            source_files.add(os.path.join(dirpath, f).replace(os.sep, '/'))

for dirpath, dirs, files in os.walk(src_root):
    for f in files:
        if f.endswith(('.hpp', '.h', '.cpp')):
            source_files.add(os.path.join(dirpath, f).replace(os.sep, '/'))

include_re = re.compile(r'#include\s*[<"]([^>"]+)[>"]')

def resolve_include(inc, from_file):
    # Try as path from root
    for base in [root, src_root]:
        candidate = os.path.join(base, inc).replace(os.sep, '/')
        if os.path.exists(candidate):
            return candidate
    # Try relative to the including file
    from_dir = os.path.dirname(from_file)
    candidate = os.path.join(from_dir, inc).replace(os.sep, '/')
    if os.path.exists(candidate):
        return candidate
    # Try basename match in mc/
    basename = os.path.basename(inc)
    for mf in mc_files:
        if mf.endswith('/' + basename):
            return mf
    return None

def get_includes(filepath):
    includes = []
    try:
        with open(filepath, 'r', errors='ignore') as f:
            for line in f:
                m = include_re.search(line)
                if m:
                    includes.append(m.group(1))
    except:
        pass
    return includes

# BFS from all non-mc files to find all transitively needed mc/ files
needed = set()
queue = list(source_files)
visited = set(source_files)

while queue:
    current = queue.pop()
    for inc in get_includes(current):
        resolved = resolve_include(inc, current)
        if resolved and resolved in mc_files:
            if resolved not in needed:
                needed.add(resolved)
            if resolved not in visited:
                visited.add(resolved)
                queue.append(resolved)

to_delete = mc_files - needed
print(f'Total mc/ files: {len(mc_files)}')
print(f'Needed mc/ files: {len(needed)}')
print(f'Can delete: {len(to_delete)}')
print()
for f in sorted(to_delete):
    print(f)
