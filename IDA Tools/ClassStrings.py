import idautils
import idaapi
import idc
import ida_kernwin

# User Input
class_to_search = ida_kernwin.ask_str("", 0, "Enter name of class to search for:")
output_file = ida_kernwin.ask_file(True, "output.txt", "Text files (*.txt)")

# Load all strings
all_strings = idautils.Strings()

# { [key: demangled_name]: strings[] }
data = {}

# Track any strings that are only used once
unique_strings = []

# Iterate every string in the idb
# Check all of the strings xrefs to find where it is called if it starts with the class name
# Todo: Make this work if there are return types?
for string in all_strings:
    xrefs = idautils.XrefsTo(string.ea)
    used = False
    count = 0

    for xref in xrefs:
        count = count + 1
        mangled_name = idc.get_func_name(xref.frm)
        demangled_name: str = idaapi.demangle_name(mangled_name, 0)

        if demangled_name != None:
            if demangled_name.startswith(class_to_search + "::"):
                if demangled_name not in data:
                    data[demangled_name] = []

                data[demangled_name].append(str(string))
                used = True

    if count == 1 and used:
        unique_strings.append(str(string))

text_output = f"//\n// Strings dumped by ClassStrings.py\n//\n\n"

# Format text with results
for key in data.keys():
    text_output += f"{key}\n"

    for string in data[key]:
        if string in unique_strings:
            text_output += f"    [UNIQUE] \"{string}\"\n"
        else:            
            text_output += f"    \"{string}\"\n"

    text_output += "\n"

with open(output_file, "w") as file_handle:
    file_handle.write(text_output)

print(f"Found {len(data.keys())} functions in class {class_to_search} with strings")
print(f"Saved output to {output_file}")