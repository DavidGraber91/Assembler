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

## 🔍 Deep Dive into Features
### 1. Macro Expansion (The Pre-Assembler)
A Macro is a shortcut for a sequence of instructions. Instead of writing the same block of code multiple times, a programmer defines a macro once.
What your tool does: The Pre-Assembler scans the .as file, identifies macro definitions (between mcr and endmcr), and replaces every macro call with its full content.
The Output: A cleaned-up .am file, ready for the core translation process.

### 2. Comprehensive Error Handling
Your assembler doesn't just crash when it sees bad code; it helps the programmer find the problem. It detects:
Syntax Errors: Missing commas, illegal characters, or unbalanced brackets.
Logic Errors: Using a non-existent label or a register name that is misspelled.
Constraint Violations: Numbers that exceed the 14-bit capacity or trying to use a register where an immediate value is required.
Clear Reporting: Errors are printed with the specific line number from the source file.

### 3. Detailed Output Files
Upon a successful run, the assembler generates three types of files to be used by a Linker or a Virtual Machine:
.ob (Object File): The heart of the output. It contains the instruction counter (IC) and the encoded 14-bit words using the unique four-character encoding (*, #, %, !).
.ent (Entry File): Lists all symbols defined with the .entry directive and their corresponding memory addresses.
.ext (External File): Lists all symbols that were declared as .extern and the specific addresses where they were used in the code.

## 🧩 The Encoding Logic (14-bit System)
The "imaginary computer" this project targets uses a 14-bit word size. Your assembler handles this by splitting the translation into specific bit-fields:
Opcode: 4 bits (determining the instruction type like mov or add)
Addressing Methods: Bits dedicated to Source and Target operands.
ARE (2 bits): Absolute, Relocatable, or External. This is crucial for the linking process. 

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

### Usage
Run the assembler by providing the filenames (without the .as extension):

./p_assembler file1 file2


## Academic Context
This project was developed at The Open University as part of the Computer Science curriculum. It demonstrates proficiency in manual memory management in C, understanding of CPU architecture, and compiler design principles.


