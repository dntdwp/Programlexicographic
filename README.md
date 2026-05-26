deskripsi program 
Aplikasi suggestion berbasis teks yang membantu user menemukan kata dari kamus berdasarkan prefix yang diketik. Kamus berisi 100 kata yang dibaca dari file, disimpan dalam BST, dan hasil suggestion ditampilkan secara terurut alfabetis.

Requirements
Functional Requirements:

1. Aplikasi membaca 100 kata dari file kamus.txt saat program dijalankan
2. Kata-kata tersebut disimpan ke dalam BST secara otomatis terurut
3. User dapat mengetik prefix lalu tekan Enter untuk mendapatkan suggestion
4. Aplikasi menampilkan semua kata yang awalannya cocok dengan prefix
5. Suggestion ditampilkan secara terurut alfabetis (suggestion disimpan didalam Queue)
6. User dapat memilih suggestion dari output yang ada untuk dijadikan satu kalimat (suggestion yang dipilih oleh user disimpan didalam Queue)
7. User dapat melakukan pencarian berkali-kali dan menyusun kalimat tanpa restart program

Batasan:
100 kata dalam kamus
Panjang kata maksimal 31 karakter
Panjang prefix input maksimal 31 karakter
