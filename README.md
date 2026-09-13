# Program Lexicographic — BST + Queue in C

Indonesian dictionary autocomplete (prefix suggestion) + synonym finder + sentence builder.
Coursework: Struktur Data dan Algoritma, JTK Politeknik Negeri Bandung.

![C](https://img.shields.io/badge/C-A8B9CC?style=flat&logo=c&logoColor=black)

## ✨ Features
- **Prefix autocomplete** — ketik prefix, dapat semua kata yang cocok, terurut alfabetis (BST in-order + Queue)
- **Synonym search** — cari sinonim dari `Tesaurus-BahasaIndonesia.txt`
- **Print Tree** — visualisasi isi BST
- **Sentence builder** — pilih suggestion berkali-kali untuk susun kalimat tanpa restart

## 🛠️ Tech
- Language: C (C99)
- ADT: Binary Search Tree (`binTree.c/h`), Queue (`queue.c/h`)
- Dataset: `Tesaurus-BahasaIndonesia.txt` (100 kata, max 31 char)

## 📁 Structure
```
main.c        # menu + UI loop
binTree.c/h   # BST: insert, prefix search, print
queue.c/h     # Queue: tampung suggestion & kalimat
boolean2.h    # tipe boolean
```

## 🚀 How to Run
```bash
gcc main.c binTree.c queue.c -o kamus
./kamus
# Windows: kamus.exe
```
Pastikan `Tesaurus-BahasaIndonesia.txt` satu folder sama exe.

Example:
```
1. Mencari Prefix
Masukkan prefix: bela
--- Suggestion untuk "bela" ---
Total: X kata ditemukan.
```

## 🎓 What I Learned
- BST insertion & in-order traversal for sorted autocomplete
- Combining two ADTs (BST for storage, Queue for results)
- File I/O + input validation in C

## 👤 Author
Denta Dwipawasesa — JTK'25 Polban, currently learning Go/Rust/C++
