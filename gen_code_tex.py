import os
import shutil
from typing import Optional
from glob import glob
from collections import defaultdict

root = "src"
code_files = [x[len(root)+1:] for x in glob(f"{root}/**/*.cpp", recursive=True) if x.count('.') == 1]
sections = ["section", "subsection", "subsubsection"]

shutil.rmtree("tmp")

# Make Tree
code_tree = defaultdict(dict)
for code_file in code_files:
    divs = code_file.split('/')
    section = divs[0]
    if section not in code_tree:
        code_tree[section] = defaultdict(dict)
    if "files" not in code_tree[section]:
        code_tree[section]["files"] = list()
    code_tree[section]["files"].append(code_file)


for section in code_tree:
    code_tree[section]["files"].sort()


def clean_code(file_path: str) -> str:
    with open(file_path, 'r', encoding='utf-8') as f:
        code = f.read()
        f.close()
    code = code.replace(' ' * 4, ' ' * 2)
    code = code.split('\n', 1)[-1]
    return code


# Copy source code to tmp
os.makedirs("tmp", exist_ok=True)
for code_path in code_files:
    subpath, filename = os.path.split(code_path)
    dst = os.path.join("tmp", subpath)
    os.makedirs(dst, exist_ok=True)
    src = os.path.join(root, subpath, filename)
    dst = os.path.join(dst, filename)
    with open(dst, 'w', encoding='utf-8') as f:
        f.write(clean_code(src))
        f.close()


# Generate Tex
""" Example
\\Algorithm{Title}
{Description}
{\\begin{itemize}
    \\item CheckList
\\end{itemize}}
{Time Complexity}
{ext. cpp or python}{source path}
{author}
"""

def make_format(path: str):
    splits = path.split('/')
    code_ext = splits[-1].split('.')[-1]
    title = splits[-1].split('.')[0].replace('_', ' ').title()  # TODO
    time_complexity = ""  # TODO
    description = ""  # TODO
    checklist = ""  # TODO
    author = "tony9402"  # TODO

    text = f"""
\\Algorithm{{{title}}}
{{{description}}}
{{{checklist}}}
{{{time_complexity}}}
{{{code_ext}}}{{{os.path.join("tmp", path)}}}
{{{author}}}
"""
    return text

tex = []
markdown = []
def make_tex(tree: "defaultdict", current_key: str = "", dep: int = -1):
    assert dep <= 2

    if dep >= 0:
        current_key = current_key.replace('_', ' ').title()
        section = f"\\{sections[dep]}{{{current_key}}}"
        tex.append(f"{section}")
        line = " " * dep + "- "
        line = f"{line} {current_key}"
        markdown.append(line)

    if "files" in tree:
        for file_path in tree["files"]:
            tex.append(make_format(file_path))
            line = " " * (dep + 4) + "- "
            algorithm_title = file_path.split('/')[-1].split('.')[0].replace('_', ' ').title()
            line = f"{line} [{algorithm_title}](src/{file_path})"
            markdown.append(line)

    for k, v in tree.items():
        if k != "files":
            make_tex(v, k, dep + 1)


make_tex(code_tree)

with open("code.tex", encoding="utf-8", mode="w") as f:
    f.write("\n\n".join(tex))
    f.close()

with open("README.md", encoding='utf-8', mode='w') as f:
    f.write("# Teamnote\n\n")
    f.write("\n".join(markdown))
    f.close()