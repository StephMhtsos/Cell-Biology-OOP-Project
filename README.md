#  Cell Biology Simulation in C++

A C++ object-oriented simulation of core cellular biology processes — including DNA transcription and RNA translation into proteins — modelled after real biological structures like the nucleus, ribosome, and cytoplasm.

---

## Overview

This project simulates the **Central Dogma of Molecular Biology**:

```
DNA → (Transcription) → RNA → (Translation) → Protein
```

The program models a living cell with a nucleus containing genes, and a cytoplasm full of ribosomes that synthesize proteins across multiple cell cycles.

---

##🏗rchitecture

The simulation is built around the following classes:

| Class | Role |
|---|---|
| `Sequence` | Abstract base class for biological sequences |
| `DNA` | Stores and validates DNA sequences (`A`, `C`, `G`, `T`) |
| `RNA` | Stores and validates RNA sequences (`A`, `C`, `G`, `U`) |
| `Protein` | Stores and validates protein sequences (standard amino acid codes) |
| `Gene` | Wraps a DNA sequence and handles transcription to RNA |
| `Nucleus` | Contains a collection of genes and orchestrates transcription |
| `Ribosome` | Translates RNA into a protein using codon lookup |
| `Cytoplasm` | Holds a pool of ribosomes |
| `Cell` | Top-level class combining `Nucleus` and `Cytoplasm` to run protein synthesis |

---

## ⚙️ How It Works

### Transcription (DNA → RNA)
Each base in the DNA is complementarily transcribed:
```
A → U    T → A    C → G    G → C
```

### Translation (RNA → Protein)
The RNA is read in triplets (codons). Each codon maps to an amino acid using the standard genetic code. Stop codons and unknown codons are silently skipped.

### Cell Cycle
Each cycle:
1. The user provides `K` DNA sequences (invalid sequences are rejected and re-prompted).
2. A `Cell` is created with a `Nucleus` (holding the genes) and a `Cytoplasm` (holding `L` ribosomes).
3. All genes are transcribed into RNA.
4. RNA strands are distributed across ribosomes (round-robin) and translated into proteins.
5. The full cell state is printed.

---

## Getting Started

### Prerequisites
- A C++11 (or later) compiler, e.g. `g++` or `clang++`

### Compile

```bash
g++ -std=c++11 -o cell_sim main.cpp
```

### Run

```bash
./cell_sim K L M
```

| Argument | Description |
|---|---|
| `K` | Number of DNA sequences (genes) per cell |
| `L` | Number of ribosomes in the cytoplasm |
| `M` | Number of cell cycles to simulate |

### Example

```bash
./cell_sim 2 3 1
```

```
=== Cycle 1 ===
Enter DNA sequence: ATGCGT
Enter DNA sequence: TACGCA
Nucleus created with 2 genes
Transcribed RNA: UACGCA (length=6) Valid? Yes
Transcribed RNA: AUGCGU (length=6) Valid? Yes
Produced Protein: YA (length=2) Valid? Yes
Produced Protein: MR (length=2) Valid? Yes
--- CELL STATE ---
...
```

---

##  Input Validation

- **DNA**: Only `A`, `C`, `G`, `T` are accepted. Invalid sequences are rejected with a message.
- **RNA**: Only `A`, `C`, `G`, `U` are accepted.
- **Protein**: Only the 20 standard amino acid single-letter codes are accepted.

---

## Project Structure

```
.
└── main.cpp      # All class definitions and main entry point
```

---

##  Biological Accuracy Notes

- Transcription follows standard Watson-Crick base pairing rules.
- The codon table covers all 20 amino acids with their full set of synonymous codons.
- Stop codons (`UAA`, `UAG`, `UGA`) are not mapped and result in translation termination (skipped).
- This is a simplified model — features like start codon enforcement, introns, and post-translational modifications are not included.

---

## License

This project is open source. Feel free to use and extend it for educational purposes.
