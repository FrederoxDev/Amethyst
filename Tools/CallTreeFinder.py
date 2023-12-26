import os
import json
import idautils
import idc
import ida_funcs
import ida_name

tools_folder = os.environ.get("appdata") + "/Amethyst/tools/"
results_path = tools_folder + "call_tree_search.json"
logs_path = tools_folder + "logs.txt"
logs = ""

found_count = 0

data = {}
with open(results_path, "r") as file_handle:
    data = json.loads(file_handle.read())

for function_ea in idautils.Functions():
    found_function_name: str = idc.get_func_name(function_ea)

    # This is a func which has been found on other and has one xref
    if found_function_name in data:
        function_xrefs_to = list(idautils.XrefsTo(function_ea))
        print(len(function_xrefs_to))

# Check if the known function has one xref like the other
# for known_func_symbol in data.keys():
#     function_ea = symbol_to_func_ea[known_func_symbol]
#     xref_symbol_name = data[known_func_symbol]

#     # For now only do the most basic search of functions with one xref
#     function_xrefs_to = list(idautils.XrefsTo(function_ea))
#     if len(function_xrefs_to) != 1:
#         continue

#     print(known_func_symbol)

#     found_function_name: str = idc.get_func_name(function_xrefs_to[0].frm)

#     xref_function = ida_funcs.get_func(function_xrefs_to[0].frm)
#     if xref_function == None:
#         continue

#     ida_name.set_name(function.start_ea, xref_symbol_name)

#     print(f"Renamed {found_function_name} to {xref_symbol_name}\n")
#     logs += f"Renamed {found_function_name} to {xref_symbol_name}\n\n"
#     found_count = found_count + 1

print(f"Found and renamed {found_count} functions!")
logs = f"// Found {found_count} functions!\n\n" + logs

with open(logs_path, "w") as file_handle:
    file_handle.write(logs)