import idautils
import idaapi
import idc
import ida_kernwin
import ida_funcs
import ida_name
from typing import TypedDict, List
import json

class StringInfo(TypedDict):
    was_unique: bool
    string: str

input_file = ida_kernwin.ask_file(False, "output.json", "JSON (*.json)")
logs_file = ida_kernwin.ask_file(True, "logs.txt", "txt (*.txt)")

logs = ""
found_count = 0

dumped_data = {}

with open(input_file, "r") as file_handle:
    dumped_data = json.loads(file_handle.read())

unique_strings = {}

# Pre-Process strings and find all unique ones
# Store in the dict with the key as the string 
for string in idautils.Strings():
    string_xrefs = list(idautils.XrefsTo(string.ea))
    if len(string_xrefs) != 1:
        continue

    # Store function xref in dict
    unique_strings[str(string)] = string_xrefs[0]

# Iterate through the mangled names and lookup their unique strings in pre-processed dict
for mangled_name in dumped_data.keys():
    function_strings: List[StringInfo] = dumped_data[mangled_name]
    
    for function_string in function_strings:
        if not function_string["was_unique"]:
            continue

        if not function_string["string"] in unique_strings:
            continue

        func_xref = unique_strings[function_string["string"]]
        found_function_name: str = idc.get_func_name(func_xref.frm)

        # Function has already been labeled in the past
        if found_function_name == mangled_name:
            print(f"{mangled_name} already found!\n")
            logs += f"{mangled_name} already found!\n\n"
            break

        # Function sometimes just isnt found?
        function = ida_funcs.get_func(func_xref.frm)
        if function == None:
            print(f"Failed to get {found_function_name} from xref?\n")
            logs += f"Failed to get {found_function_name} from xref?\n\n"
            break

        print(f"Renamed {found_function_name} to {mangled_name} based on \"{function_string['string']}\"\n")
        logs += f"Renamed {found_function_name} to {mangled_name} based on \"{function_string['string']}\"\n\n"

        # Rename the function to the symbol found
        found_count = found_count + 1
        ida_name.set_name(function.start_ea, mangled_name)
        break

logs = f"// Found {found_count} functions!\n\n" + logs

with open(logs_file, "w") as file_handle:
    file_handle.write(logs)