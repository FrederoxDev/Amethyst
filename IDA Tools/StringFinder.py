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

dumped_data = {}

with open(input_file, "r") as file_handle:
    dumped_data = json.loads(file_handle.read())

all_strings = idautils.Strings()

def find_string(string_to_find: str):
    for string in all_strings:
        if str(string) == string_to_find:
            return string
        
    return None

for mangled_name in dumped_data.keys():
    function_strings: List[StringInfo] = dumped_data[mangled_name]
    
    for function_string in function_strings:
        # For now don't search non-unique strings
        # Maybe come back and do a combined search of all function strings
        # E.g. a function could be the only one with two specific strings
        if not function_string["was_unique"]:
            continue

        # Try and find the string at all 
        result = find_string(function_string["string"])
        if result == None:
            continue

        # Xref the string and see if only one function uses it here too
        xrefs = list(idautils.XrefsTo(result.ea))
        if len(xrefs) != 1:
            continue

        found_function_name: str = idc.get_func_name(xrefs[0].frm)

        # Check its not already been named in the past
        if found_function_name == mangled_name:
            print(f"{mangled_name} already found!")
            break
            
        print(f"renaming {found_function_name} to {mangled_name} based on \"{function_string['string']}\"\n")

        # Function sometimes just isnt found?
        function = ida_funcs.get_func(xrefs[0].frm)
        if function == None:
            print(f"Failed to get {found_function_name} from xref?")
            break

        # Rename the function to the symbol found
        ida_name.set_name(function.start_ea, mangled_name)
        break