import os
import json
import idautils
import idc

tools_folder = os.environ.get("appdata") + "/Amethyst/tools/"
known_funcs_path = tools_folder + "known_funcs.json"
results_path = tools_folder + "call_tree_search.json"
known_client_func_symbols = []

with open(known_funcs_path, "r") as file_handle:
    known_client_func_symbols = json.loads(file_handle.read())

# Map the functions known on client to functions known here
found_funcs = {} # Key: mangled name, Value: ea 

for function_ea in idautils.Functions():
    func_symbol: str = idc.get_func_name(function_ea)

    # Unable to find the symbol from client in this version
    if func_symbol not in known_client_func_symbols:
        continue

    found_funcs[func_symbol] = function_ea

print(f"Found {len(found_funcs.keys())} / {len(known_client_func_symbols)} functions from client")

data = {}

# Search upwards for functions 
for symbol in found_funcs.keys():
    function_ea = found_funcs[symbol]

    # For now only do the most basic search of functions with one xref
    function_xrefs_to = list(idautils.XrefsTo(function_ea))
    if len(function_xrefs_to) != 1:
        continue

    found_function_name: str = idc.get_func_name(function_xrefs_to[0].frm)
    if found_function_name == "":
        continue

    if found_function_name in known_client_func_symbols:
        continue

    data[symbol] = found_function_name 

# Dump data back to file
with open(results_path, "w") as file_handle:
    file_handle.write(json.dumps(data))

    print(f"Found {len(data.keys())} functions to search, dumping to {os.path.abspath(file_handle.name)}")