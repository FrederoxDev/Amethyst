import idautils
import idaapi
import idc
import ida_kernwin
from typing import TypedDict
import json

# User Input
# class_to_search = ida_kernwin.ask_str("", 0, "Enter name of class to search for:")

classes_to_search = ["ClientInstance"]
output_file = ida_kernwin.ask_file(True, "output.json", "JSON (*.json)")

# Load all strings
all_strings = idautils.Strings()

# Key: mangled name, Value: strings
dumped_data = {}

class FunctionInfo(TypedDict):
    mangled_name: str
    class_name: str
    function_name: str

def get_class_info(mangled_name: str) -> FunctionInfo | None: 
    # Some symbols just fail to demangle idk why
    demangled_name: str = idaapi.demangle_name(mangled_name, 0)
    if demangled_name == None:
        return None

    demangled_name = demangled_name.split("(")[0]

    # There is probably a return type so get the right hand side
    if " " in demangled_name:
        split = demangled_name.split(" ")
        demangled_name = split.pop()

    # Should be left with ClassName::FunctionName
    # Or in some cases Namespace::ClassName::FunctionName
    split = demangled_name.split("::")
    function_name = split.pop() 
    class_name = "::".join(split) 

    return {
        "mangled_name": mangled_name,
        "class_name": class_name,
        "function_name": function_name
    }

class StringInfo(TypedDict):
    was_unique: bool
    string: str

# Search all xrefs of all strings for the classes we're looking for
for string in all_strings:
    xrefs = list(idautils.XrefsTo(string.ea))

    for xref in xrefs:
        mangled_name: str = idc.get_func_name(xref.frm)
        func_info = get_class_info(mangled_name)

        # If it is unable to demangle the symbol
        if func_info == None:
            continue

        if func_info["class_name"] in classes_to_search:
            # Ensure there is an empty array for the function
            if mangled_name not in dumped_data:
                dumped_data[mangled_name] = []

            dumped_data[mangled_name].append({
                "was_unique": len(xrefs) == 1,
                "string": str(string)
            })

with open(output_file, "w") as file_handle:
    file_handle.write(json.dumps(dumped_data))