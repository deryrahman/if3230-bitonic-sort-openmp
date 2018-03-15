# Bitonic Sort

Tugas OpenMP - Bitonic Sort. Praktikum1_K01_13515097

## Petunjuk penggunaan program

1. Buka terminal, jalankan make
    ```sh
    $ make
    ```
2. Untuk menjalankan program, ketik
    ```sh
    $ ./bitonic_sort <n> <p>
    ```
    - <n> : problem size / banyaknya elemen random
    - <p> : thread number (optional) (default : ``omp_get_max_threads``)

## Pembagian tugas

| NIM | Nama | Tugas |
| ------ | ------ | ------ |
| 13515097 | Dery Rahman A | All |

## Laporan

### Deskripsi solusi paralel
Bitonic sort merupakan salah satu teknik sorting network yang dapat diparalelkan, dengan kompleksitas O(log<sup>2</sup>n). Konsep bitonic sort sendiri yaitu dengan membuat bitonic subsequence pada tiap iterasinya. Sequence ``0..n`` dikatakan **bitonic increasing** jika terdapat subsequence ``0..a`` menaik, dan ``a..n`` menurun, dan dikatakan **bitonic decreasing** jika terdapat subsequence ``0..a`` menurun, dan ``a..n`` menaik ``(0<=a<=n)``.

Untuk mendapatkan sequence bitonic, dapat dilakukan dengan cara membandingkan 2 buah nilai pada sequence, dengan sequence perbandingan yang independent terhadap data (perbandingan antara 2 nilai dengan perbandingan antara 2 nilai yang lain, tidak saling bergantung). Sehingga, pada titik inilah kita dapat memparalelkan.

<div style="text-align:center"><img src ="docs/bitonic.png" /></div>
<p style="text-align: center;">Ilustrasi 1.1</p>

Pada ilustrasi, tahap A,B,C,...O dapat dilakukan secara paralel, karena data tidak saling bergantung ketika dilakukan operasi perbandingan.

### Analisis solusi
Solusi yang saya buat adalah dengan melakukan paralelisasi pada bagian operasi perbandingan. Dengan menggunakan 2 thread, saya mendapatkan peningkatan kecepatan sebesar ~1.5-1.9x lipat jika dibandingkan dengan serial.

Pada dasarnya bitonic sort hanya bisa melakukan sorting elemen yang berjumlah 2 pangkat. Oleh karena itu, untuk menghandle elemen yang tidak berjumlah 2 pangkat, saya membuat elemen dummy, yaitu elemen maximum pada ``n`` buah elemen, kemudian menambahkan elemen maximum sebanyak ``dummy_n-n`` buah elemen. ``dummy_n`` merupakan bilangan 2 pangkat terdekat setelah ``n``.

**update 15/03/2018**

Setelah mencoba menggunakan server ITB dengan 64 core, saya menggunakan thread sebanyak ``8`` untuk problem size 5000, ``16`` untuk problem size 50000 dan 100000, dan ``32`` untuk 200000 dan 400000. Speedup yang didapat ~2.5-11.1x lipat.

**Solusi kinerja yang lebih baik**

Untuk ukuran problem size yang besar, lebih efektif menggunakan komputer yang mempunyai jumlah core yang banyak, sehingga thread yang dibuat bisa lebih banyak. Oleh karena itu, untuk ukuran problem size 400000, efektif menggunakan 32 thread. Jika ingin menggunakan 64 thread, yang perlu dilakukan adalah menambah problem sizenya. Saya mencoba, dengan menggunakan 64 thread, problem size 100 juta, memberikan speedup hingga ``17.569x``.

Untuk problem size dengan jumlah elemen yang bukan 2 pangkat, tentu dengan menggunakan elemen dummy, membuat komputer melakukan operasi perbandingan yang tidak diperlukan, oleh karena itu, mungkin bisa dilakukan [solusi lain](http://www.iti.fh-flensburg.de/lang/algorithmen/sortieren/bitonic/oddn.htm)

Selain itu, bisa juga dengan meminimalkan komunikasi dan mengoptimasi *local computation* [sumber](http://web.mst.edu/~ercal/387/slides/Bitonic-Sort97.pdf)

~~Solusi lain, bisa dengan menambahkan core, sehingga bisa menambah maksimum thread yg efektif.~~

### Jumlah thread
Saya menggunakan jumlah thread sebanyak 2 buah dikarenakan jumlah core pada komputer saya berjumlah 2 buah core. Jika menggunakan thread lebih dari banyaknya core pada komputer tersebut, maka akan timbul overhead yang dapat menurunkan kinerja. Oleh karena itu, saya menggunakan fungsi ``omp_get_max_threads();`` untuk mendapatkan maksimum thread yang dapat bekerja dengan baik pada komputer tersebut.

**update 15/03/2018**

Selain itu, dengan server ITB, menggunakan thread sebanyak ``8`` untuk problem size 5000, ``16`` untuk problem size 50000 dan 100000, dan ``32`` untuk 200000 dan 400000. Speedup yang didapat ~2.5-11.1x lipat. Hal ini dipilih karena berdasarkan eksperimen menggunakan 2,4,8,16, dan 32 thread untuk setiap problem size. Eksperimen dilakukan sebanyak 3x dan diambil rata-ratanya. Saya tidak menggunakan 64 thread, karena berdasarkan eksperimen, problem size 400000 dengan 64 thread memberikan speedup yang buruk. <1x lipat.

| N | 2 | 4 | 8 | 16 | 32 |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| **5.000** | 1.287x | 1.836x | **2.781x** | 1.174x | 0.328x |
| **50.000** | 1.679x | 2.809x | 4.711x | **5.916x** | 3.738x |
| **100.000** | 1.537x | 2.844x | 4.333x | **7.088x** | 5.173x |
| **200.000** | 1.684x | 2.945x | 5.635x | 8.013x | **8.657x** |
| **400.000** | 1.714x | 3.119x | 5.325x | 6.959x | **11.020x** |

Untu 64 thread, berfungsi dengan baik untuk problem size diatas 1000000, berdasarkan eksperimen berikut

| Problem size | Speedup |
| ------ | ------ |
| **100.000** | 0.099x |
| **1.000.000** | 1.034x |
| **10.000.000** | 7.324x |
| **100.000.000** | 17.569x |

### Pengukuran kinerja
Berikut adalah hasil dari pengukuran kinerja dengan jumlah elemen 5000, 50000, 100000, 200000, 400000. Setiap pengujian dilakukan sebanyak 3 kali dan dihitung rata-ratanya. Prosesor yang digunakan adalah 2,3 GHz Intel Core i5 (7360U) 2 cores.


| | N | Percobaan 1 | Percobaan 2 | Percobaan 3 | Avg | Speedup |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| **Serial time** (micro second) | **5.000** | 3657 | 3447 | 3745 | 3616.333 | - |
| **Paralel time** (micro second) | **5.000** | 2454 | 2410 | 2353 | 2405.667 | **1.503x** |
| **Serial time** (micro second) | **50.000** | 53295 | 57043 | 46795 | 52377.667 | - |
| **Paralel time** (micro second) | **50.000** | 27071 | 34690 | 36051 | 32604 | **1.606x** |
| **Serial time** (micro second) | **100.000** | 98679 | 95753 | 102108 | 98846.667 | - |
| **Paralel time** (micro second) | **100.000** | 55557 | 61413 | 55448 | 57472.667 | **1.719x** |
| **Serial time** (micro second) | **200.000** | 204232 | 194476 | 197580 | 198762.667 | - |
| **Paralel time** (micro second) | **200.000** | 110442 | 110062 | 108968 | 109824 | **1.809x** |
| **Serial time** (micro second) | **400.000** | 422364 | 428631 | 451095 | 434030 | - |
| **Paralel time** (micro second) | **400.000** | 241812 | 237605 | 242812 | 240743 | **1.803x** |

Berikut adalah hasil dari pengukuran kinerja dengan prosesor 64 core (server ITB)

| | N | Percobaan 1 | Percobaan 2 | Percobaan 3 | Avg | Speedup |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| **Serial time** (micro second) | **5.000** | 4736 | 4544 | 4764 | 4681.333 | - |
| **Paralel time** (micro second) | **5.000** | 1979 | 1558 | 1506 | 1681 | **2.785x** |
| **Serial time** (micro second) | **50.000** | 57576 | 58251 | 59762 | 58529.667 | - |
| **Paralel time** (micro second) | **50.000** | 10845 | 12117 | 13001 | 11987.667 | **4.882x** |
| **Serial time** (micro second) | **100.000** | 129816 | 127849 | 127559 | 128408 | - |
| **Paralel time** (micro second) | **100.000** | 13091 | 16998 | 13076 | 14388.333 | **8.924x** |
| **Serial time** (micro second) | **200.000** | 296059 | 301991 | 301991 | 300013.667 | - |
| **Paralel time** (micro second) | **200.000** | 29949 | 32308 | 54116 | 38791 | **7.734x** |
| **Serial time** (micro second) | **400.000** | 671679 | 632210 | 669148 | 657679 | - |
| **Paralel time** (micro second) | **400.000** | 67982 | 62973 | 59741 | 63565.333 | **10.346x** |

### Analisis perbandingan kinerja
Pada percobaan  terlihat bahwa speedup cenderung semakin tinggi ketika problem size ditingkatkan. Hal ini dikarenakan peningkatan ``T``<sub>overhead</sub> lebih kecil dibandingkan dengan ``T``<sub>serial</sub>. Oleh karena itu, semakin besar problem size, speedup cenderung meningkat, namun tidak akan lebih dari ``p`` kali. (``p`` banyaknya thread yang digunakan) (``T``<sub>paralel</sub> = ``T``<sub>serial</sub>/``p`` + ``T``<sub>overhead</sub>) (speedup = ``T``<sub>serial</sub>/``T``<sub>paralel</sub>)

### References
- [https://www2.cs.duke.edu/courses/fall08/cps196.1/Pthreads/bitonic.c](https://www2.cs.duke.edu/courses/fall08/cps196.1/Pthreads/bitonic.c)
- [http://www.iti.fh-flensburg.de/lang/algorithmen/sortieren/bitonic/bitonicen.htm](http://www.iti.fh-flensburg.de/lang/algorithmen/sortieren/bitonic/bitonicen.htm)
