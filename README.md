# Assembler

# 🖥️ Custom Virtual Machine Assembler

## 📌 Overview
This project is a full **Assembler** written in **C**, developed as a final project for the "System Programming Laboratory" course. The program translates source code written in a unique Assembly language into machine code for a 14-bit imaginary computer architecture.

The project features a complete processing pipeline: from macro expansion to the generation of binary object files encoded in a custom format.

---

## 🏗️ Architecture & Pipeline
The assembler operates in three main stages:

1.  **Pre-Assembler:** * Scans the source file (`.as`).
    * Identifies and expands Macros into a filtered file (`.am`).
2.  **First Pass:**
    * Builds the **Symbol Table**.
    * Calculates memory addresses for instructions and data (IC & DC).
    * Handles directives like `.define`, `.extern`, and `.entry`.
3.  **Second Pass:**
    * Performs final translation of instructions into binary code.
    * Resolves label addresses.
    * Generates output files (`.ob`, `.ent`, `.ext`).

---

## 🛠️ Technical Features
* **Addressing Modes:** Supports Immediate (`#`), Direct, Index (`array[r3]`), and Register (`r0-r7`) addressing.
* **Dynamic Memory Management:** Utilizes Linked Lists to manage symbols and code lines, allowing for flexible input sizes.
* **Error Detection:** Comprehensive error reporting for syntax errors, out-of-range values, undefined labels, and more.
* **ARE Encoding:** Implements Absolute, Relocatable, and External (ARE) flags for linker compatibility.

---

## 💾 The Special Output Format (.ob)
The output of this assembler is unique. Instead of standard binary or hex, it encodes every 2 bits into a specific character set to represent the 14-bit word.

**Encoding Table:**
| Bits | Character |
| :--- | :--- |
| 00   | `*` |
| 01   | `#` |
| 10   | `%` |
| 11   | `!` |

### Example Translation:
If a line of Assembly is `MOV r3, r5`, it might be encoded into a 14-bit binary string:
`00000010110100`

In your `.ob` file, it will appear as:
`* * % ! # *`

---

## 📂 Project Structure
* `main.c`: Entry point. Orchestrates the flow between the pre-assembler and the two passes.
* `pre_assembler/`: Logic for macro expansion and string manipulation.
* `assembler/`: Core logic including instruction parsing (`instr.c`), data directives (`directive.c`), and binary image construction (`code.c`).
* `makefile`: Automated build system.

---

## 🚀 Getting Started

### Compilation
To build the project, run:
make

###Usage
Run the assembler by providing the filenames (without the .as extension):
./p_assembler file1 file2


##Academic Context
This project was developed at The Open University as part of the Computer Science curriculum. It demonstrates proficiency in manual memory management in C, understanding of CPU architecture, and compiler design principles.


