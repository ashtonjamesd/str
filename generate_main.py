# script of laziness: generates 'run_test' functions for all 'should' declarations in 'str_tests.c'

with open("test/str_tests.c", "r") as file:
    content = file.read()

main_index = content.find("\n\nint main")
if main_index != -1:
    content = content[:main_index]

with open("test/str_tests.c", "w") as file:
    file.write(content)

    file.write("\n\nint main() {\n")

    i = 0
    while i < len(content):

        if content[i:i+6] == "should":
            start = i + 6

            while content[i] != ')':
                i += 1

            file.write(f"  run_test{content[start:i]});\n")

        i += 1

    file.write("\n  return conclude_test_runner();\n")
    file.write("}\n")