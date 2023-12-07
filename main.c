#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>

// Struct variabel data customers
typedef struct{
	char Nama[26];
	char Alamat[26];
	char NoTelp[13];
	char ID[7];
	char Password[9];
}Customer;

// Struct variabel data barang
typedef struct{
	char Nama[26];
	int Harga;
	int Kategori; //Mesin (1), Ban (2), Velg (3), Aksesoris (4), Jok/Kursi(5)
	int Jenis; //Bermotor (1) atau Bermobil (2)
}Barang;

// Fungsi boolean untuk validasi jika inputan nomor telepon berupa char
bool isDigit(char nomor[]){
	int i;

	for(i=0; nomor[i] != '\0'; i++){
		if(isdigit(nomor[i]) == 0){ // isdigit() digunakan untuk cek apakah char berupa numeric atau bukan
			return false;
		}
	}
	return true;
}

// Fungsi boolean untuk validasi jika id customer sudah ada di file sekuensial
bool CustomerIDExist(char ID[]){
	FILE *cust = fopen("customer.txt", "r"); // fopen() digunakan untuk membuka file
	Customer C;

	if(cust){
		while(!feof(cust)){
			fscanf(cust, "%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#\n", C.Nama, C.Alamat, C.NoTelp, C.ID, C.Password);

			if(strcmp(ID, C.ID) == 0){
				fclose(cust);
				return true;
			}
		}
	}

	fclose(cust);
	return false;
}

// Fungsi boolean untuk validasi jika data customer ada dan inputan id dan passwordnya tepat
bool LoginCustomer(char ID[], char Password[]){
	FILE *cust = fopen("customer.txt", "r");
	Customer C;

	if(cust){
		while(!feof(cust)){
			fscanf(cust, "%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#\n", C.Nama, C.Alamat, C.NoTelp, C.ID, C.Password);

			if(strcmp(ID, C.ID) == 0 && strcmp(Password, C.Password) == 0){
				fclose(cust);
				return true;
			}
		}
	}

	fclose(cust);
	return false;
}

// Fungsi boolean untuk validasi saat mendaftarkan id customers
bool DaftarCustomer(Customer C){
    // jika id customer == dealer maka pendaftaran id gagal
	if(strcasecmp(C.ID, "dealer") == 0){
		return false; //Jadi, mau ID nya dealer/Dealer/dealeR. Dan sebagainya, pokoknya dealer aja itu gabisa ya ges
	}

    //jika inputan C.ID belum ada, maka pendaftaran id berhasil
	if(!CustomerIDExist(C.ID)){
		FILE *cust = fopen("customer.txt", "a");

		fprintf(cust, "%s#%s#%s#%s#%s#\n", C.Nama, C.Alamat, C.NoTelp, C.ID, C.Password);

		fclose(cust);

		return true;
	}

	return false;
}

// Fungsi boolean untuk mengecek apakah data customers ada pada file sekuensial
bool IsDataCustomerExist(){
	FILE *cust = fopen("customer.txt", "r");
	bool result = false;

	if(cust){
		result = true;
	}
	fclose(cust);

	return result;
}

// Fungsi untuk melihat data customers
void LihatDataCustomer(){
	FILE *cust = fopen("customer.txt", "r");
	Customer C;

	if(cust){
		printf("+---------------------------+---------------------------+---------------+-------+----------+\n");
		printf("| Nama                      | Alamat                    | Nomor Telepon | ID    | Password |\n");
		printf("+---------------------------+---------------------------+---------------+-------+----------+\n");
		while(!feof(cust)){
			fscanf(cust, "%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#\n", C.Nama, C.Alamat, C.NoTelp, C.ID, C.Password);
			printf("| %-25s | %-25s | %-13s | %-5s | %-8s |\n", C.Nama, C.Alamat, C.NoTelp, C.ID, C.Password);
		}
		printf("+---------------------------+---------------------------+---------------+-------+----------+\n");
	}else{
		printf("Tidak Ada Data Customer!\n");
	}

	fclose(cust);
}

// Fungsi boolean untuk menghapus data customers pada file sekuensial
bool DeleteDataCustomer(char ID[]){
	FILE *cust = fopen("customer.txt", "r");
	FILE *backup = fopen("backup.txt", "a");
	Customer C;
	int count = 0;
	bool result = false;

	if(cust){
		while(!feof(cust)){
			fscanf(cust, "%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#\n", C.Nama, C.Alamat, C.NoTelp, C.ID, C.Password);

			if(strcmp(ID, C.ID) == 0){
				result = true;
			}else{
				count += 1;
				fprintf(backup, "%s#%s#%s#%s#%s#\n", C.Nama, C.Alamat, C.NoTelp, C.ID, C.Password);
			}
		}
	}else{
		printf("Tidak Ada Data Customer!\n");
	}

	fclose(cust);
	fclose(backup);

	remove("customer.txt");
	if(count == 0){
		remove("backup.txt");
	}else{
		rename("backup.txt", "customer.txt");
	}

	return result;
}

// Fungsi boolean untuk validasi apakah ada data barang yang diinput pada kategori mesin
bool IsMesinExist(char Nama[]){
	FILE *mesin = fopen("mesin.txt", "r");
	bool result = false;

	if(mesin){
		Barang B;
		while(!feof(mesin) && !result){
			fscanf(mesin, "%[^#]#%d#%d#%d#\n", B.Nama, &B.Harga, &B.Kategori, &B.Jenis);

			if(strcasecmp(B.Nama, Nama) == 0){
				result = true;
			}
		}
	}
	fclose(mesin);

	return result;
}


// Fungsi boolean untuk memasukkan data yang ditambahkan ke file mesin.txt
bool TambahMesin(Barang B){
	FILE *mesin = fopen("mesin.txt", "a");

	fprintf(mesin, "%s#%d#%d#%d#\n", B.Nama, B.Harga, B.Kategori, B.Jenis);

	fclose(mesin);

	return true;
}

// Fungsi boolean untuk validasi apakah ada data barang yang diinput pada kategori ban
bool IsBanExist(char Nama[]){
	FILE *ban = fopen("ban.txt", "r");
	bool result = false;

	if(ban){
		Barang B;
		while(!feof(ban) && !result){
			fscanf(ban, "%[^#]#%d#%d#%d#\n", B.Nama, &B.Harga, &B.Kategori, &B.Jenis);

			if(strcasecmp(B.Nama, Nama) == 0){
				result = true;
			}
		}
	}
	fclose(ban);

	return result;
}

// Fungsi boolean untuk memasukkan data yang ditambahkan ke file ban.txt
bool TambahBan(Barang B){
	FILE *ban = fopen("ban.txt", "a");

	fprintf(ban, "%s#%d#%d#%d#\n", B.Nama, B.Harga, B.Kategori, B.Jenis);

	fclose(ban);

	return true;
}

// Fungsi boolean untuk validasi apakah ada data barang yang diinput pada kategori velg
bool IsVelgExist(char Nama[]){
	FILE *velg = fopen("velg.txt", "r");
	bool result = false;

	if(velg){
		Barang B;
		while(!feof(velg) && !result){
			fscanf(velg, "%[^#]#%d#%d#%d#\n", B.Nama, &B.Harga, &B.Kategori, &B.Jenis);

			if(strcasecmp(B.Nama, Nama) == 0){
				result = true;
			}
		}
	}
	fclose(velg);

	return result;
}

// Fungsi boolean untuk memasukkan data yang ditambahkan ke file velg.txt
bool TambahVelg(Barang B){
	FILE *velg = fopen("velg.txt", "a");

	fprintf(velg, "%s#%d#%d#%d#\n", B.Nama, B.Harga, B.Kategori, B.Jenis);

	fclose(velg);

	return true;
}

// Fungsi boolean untuk validasi apakah ada data barang yang diinput pada kategori aksesoris
bool IsAksesorisExist(char Nama[]){
	FILE *aksesoris = fopen("aksesoris.txt", "r");
	bool result = false;

	if(aksesoris){
		Barang B;
		while(!feof(aksesoris) && !result){
			fscanf(aksesoris, "%[^#]#%d#%d#%d#\n", B.Nama, &B.Harga, &B.Kategori, &B.Jenis);

			if(strcasecmp(B.Nama, Nama) == 0){
				result = true;
			}
		}
	}
	fclose(aksesoris);

	return result;
}

// Fungsi boolean untuk memasukkan data yang ditambahkan ke file aksesoris.txt
bool TambahAksesoris(Barang B){
	FILE *aksesoris = fopen("aksesoris.txt", "a");

	fprintf(aksesoris, "%s#%d#%d#%d#\n", B.Nama, B.Harga, B.Kategori, B.Jenis);

	fclose(aksesoris);

	return true;
}

// Fungsi boolean untuk validasi apakah ada data barang yang diinput pada kategori jok
bool IsJokExist(char Nama[]){
	FILE *jok = fopen("jok.txt", "r");
	bool result = false;

	if(jok){
		Barang B;
		while(!feof(jok) && !result){
			fscanf(jok, "%[^#]#%d#%d#%d#\n", B.Nama, &B.Harga, &B.Kategori, &B.Jenis);

			if(strcasecmp(B.Nama, Nama) == 0){
				result = true;
			}
		}
	}
	fclose(jok);

	return result;
}

// Fungsi boolean untuk memasukkan data yang ditambahkan ke file jok.txt
bool TambahJok(Barang B){
	FILE *jok = fopen("jok.txt", "a");

	fprintf(jok, "%s#%d#%d#%d#\n", B.Nama, B.Harga, B.Kategori, B.Jenis);

	fclose(jok);

	return true;
}

// Fungsi boolean untuk validasi apakah nama barang sudah ada pada file sekuensial
// jika ada akan mengebalikan ke fungsi tambah, jika tidak kan mengembalikan nilai false
bool TambahBarang(Barang B){
	if(B.Kategori == 1){
		if(!IsMesinExist(B.Nama)){
			return TambahMesin(B);
		}
		return false;
	}else if(B.Kategori == 2){
		if(!IsBanExist(B.Nama)){
			return TambahBan(B);
		}
		return false;
	}else if(B.Kategori == 3){
		if(!IsVelgExist(B.Nama)){
			return TambahVelg(B);
		}
		return false;
	}else if(B.Kategori == 4){
		if(!IsAksesorisExist(B.Nama)){
			return TambahAksesoris(B);
		}
		return false;
	}
	if(!IsJokExist(B.Nama)){
		return TambahJok(B);
	}
	return false;
}

// Fungsi boolean dengan parameter nama barang untuk menghapus barang pada kategori mesin di file sekuensial
bool HapusMesin(char Nama[]){
	FILE *mesin = fopen("mesin.txt", "r");
	FILE *backup = fopen("backup.txt", "a");
	int count = 0;
	bool result = false;
	Barang B;

	if(mesin){
		while(!feof(mesin)){
			fscanf(mesin, "%[^#]#%d#%d#%d#\n", B.Nama, &B.Harga, &B.Kategori, &B.Jenis);

			if(strcasecmp(B.Nama, Nama) == 0){
				result = true;
			}else{
				fprintf(backup, "%s#%d#%d#%d#\n", B.Nama, B.Harga, B.Kategori, B.Jenis);
				count += 1;
			}
		}
	}

	fclose(mesin);
	fclose(backup);

	remove("mesin.txt");
	if(count > 0){
		rename("backup.txt", "mesin.txt");
	}else{
		remove("backup.txt");
	}

	return result;
}

// Fungsi boolean dengan parameter nama barang untuk menghapus barang pada kategori ban di file sekuensial
bool HapusBan(char Nama[]){
	FILE *ban = fopen("ban.txt", "r");
	FILE *backup = fopen("backup.txt", "a");
	int count = 0;
	bool result = false;
	Barang B;

	if(ban){
		while(!feof(ban)){
			fscanf(ban, "%[^#]#%d#%d#%d#\n", B.Nama, &B.Harga, &B.Kategori, &B.Jenis);

			if(strcasecmp(B.Nama, Nama) == 0){
				result = true;
			}else{
				fprintf(backup, "%s#%d#%d#%d#\n", B.Nama, B.Harga, B.Kategori, B.Jenis);
				count += 1;
			}
		}
	}

	fclose(ban);
	fclose(backup);

	remove("ban.txt");
	if(count > 0){
		rename("backup.txt", "ban.txt");
	}else{
		remove("backup.txt");
	}

	return result;
}

// Fungsi boolean dengan parameter nama barang untuk menghapus barang pada kategori velg di file sekuensial
bool HapusVelg(char Nama[]){
	FILE *velg = fopen("velg.txt", "r");
	FILE *backup = fopen("backup.txt", "a");
	int count = 0;
	bool result = false;
	Barang B;

	if(velg){
		while(!feof(velg)){
			fscanf(velg, "%[^#]#%d#%d#%d#\n", B.Nama, &B.Harga, &B.Kategori, &B.Jenis);

			if(strcasecmp(B.Nama, Nama) == 0){
				result = true;
			}else{
				fprintf(backup, "%s#%d#%d#%d#\n", B.Nama, B.Harga, B.Kategori, B.Jenis);
				count += 1;
			}
		}
	}

	fclose(velg);
	fclose(backup);

	remove("velg.txt");
	if(count > 0){
		rename("backup.txt", "velg.txt");
	}else{
		remove("backup.txt");
	}

	return result;
}

// Fungsi boolean dengan parameter nama barang untuk menghapus barang pada kategori aksesoris di file sekuensial
bool HapusAksesoris(char Nama[]){
	FILE *aksesoris = fopen("aksesoris.txt", "r");
	FILE *backup = fopen("backup.txt", "a");
	int count = 0;
	bool result = false;
	Barang B;

	if(aksesoris){
		while(!feof(aksesoris)){
			fscanf(aksesoris, "%[^#]#%d#%d#%d#\n", B.Nama, &B.Harga, &B.Kategori, &B.Jenis);

			if(strcasecmp(B.Nama, Nama) == 0){
				result = true;
			}else{
				fprintf(backup, "%s#%d#%d#%d#\n", B.Nama, B.Harga, B.Kategori, B.Jenis);
				count += 1;
			}
		}
	}

	fclose(aksesoris);
	fclose(backup);

	remove("aksesoris.txt");
	if(count > 0){
		rename("backup.txt", "aksesoris.txt");
	}else{
		remove("backup.txt");
	}

	return result;
}

// Fungsi boolean dengan parameter nama barang untuk menghapus barang pada kategori jok di file sekuensial
bool HapusJok(char Nama[]){
	FILE *jok = fopen("jok.txt", "r");
	FILE *backup = fopen("backup.txt", "a");
	int count = 0;
	bool result = false;
	Barang B;

	if(jok){
		while(!feof(jok)){
			fscanf(jok, "%[^#]#%d#%d#%d#\n", B.Nama, &B.Harga, &B.Kategori, &B.Jenis);

			if(strcasecmp(B.Nama, Nama) == 0){
				result = true;
			}else{
				fprintf(backup, "%s#%d#%d#%d#\n", B.Nama, B.Harga, B.Kategori, B.Jenis);
				count += 1;
			}
		}
	}

	fclose(jok);
	fclose(backup);

	remove("jok.txt");
	if(count > 0){
		rename("backup.txt", "jok.txt");
	}else{
		remove("backup.txt");
	}

	return result;
}

// Fungsi boolean untuk memilih kategori barang apa yang ingin dihapus
bool HapusBarang(Barang B){
	if(B.Kategori == 1){
		if(IsMesinExist(B.Nama)){
			return HapusMesin(B.Nama);
		}
		return false;
	}else if(B.Kategori == 2){
		if(IsBanExist(B.Nama)){
			return HapusBan(B.Nama);
		}
		return false;
	}else if(B.Kategori == 3){
		if(IsVelgExist(B.Nama)){
			return HapusVelg(B.Nama);
		}
		return false;
	}else if(B.Kategori == 4){
		if(IsAksesorisExist(B.Nama)){
			return HapusAksesoris(B.Nama);
		}
		return false;
	}
	if(IsJokExist(B.Nama)){
		return HapusJok(B.Nama);
	}
	return false;
}

// Fungsi yang digunakan untuk mengconvert huruf abjad ke huruf kecil
void toLower(char string[]){
	int i;

	for(i=0 ;string[i] != '\0'; i++){
		string[i] = tolower(string[i]);
	}
}

// Fungsi yang digunakan untuk mencari nama barang pada kategori mesin di file sekuensial kemudian ditampilkan
void CariMesin(char Nama[]){
	FILE *mesin = fopen("mesin.txt", "r");
	char cari[26], Jenis[9];
	int i = 0;

	printf("Pencarian Barang %s di Kategori Mesin :\n", Nama);

	strcpy(cari, Nama);
	toLower(cari);
	if(mesin){
		Barang B;
		char tempNama[26];
		while(!feof(mesin)){
			fscanf(mesin, "%[^#]#%d#%d#%d#\n", B.Nama, &B.Harga, &B.Kategori, &B.Jenis);
			strcpy(tempNama, B.Nama);
			toLower(tempNama);
			if(strstr(tempNama, cari)){
				i += 1;

				if(i == 1){
					printf("+-----+---------------------------+----------+----------+\n");
					printf("| No. | Nama                      | Harga    | Jenis    |\n");
					printf("+-----+---------------------------+----------+----------+\n");
				}

				if(B.Jenis == 1){
					strcpy(Jenis, "Bermotor");
				}else{
					strcpy(Jenis, "Bermobil");
				}

				printf("| %-3d | %-25s | %-8d | %-8s |\n", i, B.Nama, B.Harga, Jenis);
			}
		}
	}
	fclose(mesin);

	if(i > 0){
		printf("+-----+---------------------------+----------+----------+\n");
	}else{
		printf("\nBarang dengan Nama %s pada Kategori Mesin Tidak Ditemukan!\n", Nama);
	}
}

// Fungsi yang digunakan untuk mencari nama barang pada kategori ban di file sekuensial kemudian ditampilkan
void CariBan(char Nama[]){
	FILE *ban = fopen("ban.txt", "r");
	char cari[26], Jenis[9];
	int i = 0;

	printf("Pencarian Barang %s di Kategori Ban :\n", Nama);

	strcpy(cari, Nama);
	toLower(cari);
	if(ban){
		Barang B;
		char tempNama[26];
		while(!feof(ban)){
			fscanf(ban, "%[^#]#%d#%d#%d#\n", B.Nama, &B.Harga, &B.Kategori, &B.Jenis);
			strcpy(tempNama, B.Nama);
			toLower(tempNama);
			if(strstr(tempNama, cari)){
				i += 1;

				if(i == 1){
					printf("+-----+---------------------------+----------+----------+\n");
					printf("| No. | Nama                      | Harga    | Jenis    |\n");
					printf("+-----+---------------------------+----------+----------+\n");
				}

				if(B.Jenis == 1){
					strcpy(Jenis, "Bermotor");
				}else{
					strcpy(Jenis, "Bermobil");
				}

				printf("| %-3d | %-25s | %-8d | %-8s |\n", i, B.Nama, B.Harga, Jenis);
			}
		}
	}
	fclose(ban);

	if(i > 0){
		printf("+-----+---------------------------+----------+----------+\n");
	}else{
		printf("\nBarang dengan Nama %s pada Kategori Ban Tidak Ditemukan!\n", Nama);
	}
}

// Fungsi yang digunakan untuk mencari nama barang pada kategori velg di file sekuensial kemudian ditampilkan
void CariVelg(char Nama[]){
	FILE *velg = fopen("velg.txt", "r");
	char cari[26], Jenis[9];
	int i = 0;

	printf("Pencarian Barang %s di Kategori Velg :\n", Nama);

	strcpy(cari, Nama);
	toLower(cari);
	if(velg){
		Barang B;
		char tempNama[26];
		while(!feof(velg)){
			fscanf(velg, "%[^#]#%d#%d#%d#\n", B.Nama, &B.Harga, &B.Kategori, &B.Jenis);
			strcpy(tempNama, B.Nama);
			toLower(tempNama);
			if(strstr(tempNama, cari)){
				i += 1;

				if(i == 1){
					printf("+-----+---------------------------+----------+----------+\n");
					printf("| No. | Nama                      | Harga    | Jenis    |\n");
					printf("+-----+---------------------------+----------+----------+\n");
				}

				if(B.Jenis == 1){
					strcpy(Jenis, "Bermotor");
				}else{
					strcpy(Jenis, "Bermobil");
				}

				printf("| %-3d | %-25s | %-8d | %-8s |\n", i, B.Nama, B.Harga, Jenis);
			}
		}
	}
	fclose(velg);

	if(i > 0){
		printf("+-----+---------------------------+----------+----------+\n");
	}else{
		printf("\nBarang dengan Nama %s pada Kategori Velg Tidak Ditemukan!\n", Nama);
	}
}

// Fungsi yang digunakan untuk mencari nama barang pada aksesoris mesin di file sekuensial kemudian ditampilkan
void CariAksesoris(char Nama[]){
	FILE *aksesoris = fopen("aksesoris.txt", "r");
	char cari[26], Jenis[9];
	int i = 0;

	printf("Pencarian Barang %s di Kategori Aksesoris :\n", Nama);

	strcpy(cari, Nama);
	toLower(cari);
	if(aksesoris){
		Barang B;
		char tempNama[26];
		while(!feof(aksesoris)){
			fscanf(aksesoris, "%[^#]#%d#%d#%d#\n", B.Nama, &B.Harga, &B.Kategori, &B.Jenis);
			strcpy(tempNama, B.Nama);
			toLower(tempNama);
			if(strstr(tempNama, cari)){
				i += 1;

				if(i == 1){
					printf("+-----+---------------------------+----------+----------+\n");
					printf("| No. | Nama                      | Harga    | Jenis    |\n");
					printf("+-----+---------------------------+----------+----------+\n");
				}

				if(B.Jenis == 1){
					strcpy(Jenis, "Bermotor");
				}else{
					strcpy(Jenis, "Bermobil");
				}

				printf("| %-3d | %-25s | %-8d | %-8s |\n", i, B.Nama, B.Harga, Jenis);
			}
		}
	}
	fclose(aksesoris);

	if(i > 0){
		printf("+-----+---------------------------+----------+----------+\n");
	}else{
		printf("\nBarang dengan Nama %s pada Kategori Aksesoris Tidak Ditemukan!\n", Nama);
	}
}

// Fungsi yang digunakan untuk mencari nama barang pada kategori jok di file sekuensial kemudian ditampilkan
void CariJok(char Nama[]){
	FILE *jok = fopen("jok.txt", "r");
	char cari[26], Jenis[9];
	int i = 0;

	printf("Pencarian Barang %s di Kategori Jok/Kursi :\n", Nama);

	strcpy(cari, Nama);
	toLower(cari);
	if(jok){
		Barang B;
		char tempNama[26];
		while(!feof(jok)){
			fscanf(jok, "%[^#]#%d#%d#%d#\n", B.Nama, &B.Harga, &B.Kategori, &B.Jenis);
			strcpy(tempNama, B.Nama);
			toLower(tempNama);
			if(strstr(tempNama, cari)){
				i += 1;

				if(i == 1){
					printf("+-----+---------------------------+----------+----------+\n");
					printf("| No. | Nama                      | Harga    | Jenis    |\n");
					printf("+-----+---------------------------+----------+----------+\n");
				}

				if(B.Jenis == 1){
					strcpy(Jenis, "Bermotor");
				}else{
					strcpy(Jenis, "Bermobil");
				}

				printf("| %-3d | %-25s | %-8d | %-8s |\n", i, B.Nama, B.Harga, Jenis);
			}
		}
	}
	fclose(jok);

	if(i > 0){
		printf("+-----+---------------------------+----------+----------+\n");
	}else{
		printf("\nBarang dengan Nama %s pada Kategori Jok/Kursi Tidak Ditemukan!\n", Nama);
	}
}

// Fungsi Struct untuk mendapatkan data barang kategori mesin pada file sekuensial mesin.txt dengan parameter nama barang
Barang getMesin(char Nama[]){
	FILE *mesin = fopen("mesin.txt", "r");
	Barang B;

	if(mesin){
		while(!feof(mesin)){
			fscanf(mesin, "%[^#]#%d#%d#%d#\n", B.Nama, &B.Harga, &B.Kategori, &B.Jenis);

			if(strcasecmp(B.Nama, Nama) == 0){
				break;
			}
		}
	}
	fclose(mesin);

	return B;
}

// Fungsi Struct untuk mendapatkan data barang kategori ban pada file sekuensial ban.txt dengan parameter nama barang
Barang getBan(char Nama[]){
	FILE *ban = fopen("ban.txt", "r");
	Barang B;

	if(ban){
		while(!feof(ban)){
			fscanf(ban, "%[^#]#%d#%d#%d#\n", B.Nama, &B.Harga, &B.Kategori, &B.Jenis);

			if(strcasecmp(B.Nama, Nama) == 0){
				break;
			}
		}
	}
	fclose(ban);

	return B;
}

// Fungsi Struct untuk mendapatkan data barang kategori velg pada file sekuensial velg.txt dengan parameter nama barang
Barang getVelg(char Nama[]){
	FILE *velg = fopen("velg.txt", "r");
	Barang B;

	if(velg){
		while(!feof(velg)){
			fscanf(velg, "%[^#]#%d#%d#%d#\n", B.Nama, &B.Harga, &B.Kategori, &B.Jenis);

			if(strcasecmp(B.Nama, Nama) == 0){
				break;
			}
		}
	}
	fclose(velg);

	return B;
}

// Fungsi Struct untuk mendapatkan data barang kategori aksesoris pada file sekuensial aksesoris.txt dengan parameter nama barang
Barang getAksesoris(char Nama[]){
	FILE *aksesoris = fopen("aksesoris.txt", "r");
	Barang B;

	if(aksesoris){
		while(!feof(aksesoris)){
			fscanf(aksesoris, "%[^#]#%d#%d#%d#\n", B.Nama, &B.Harga, &B.Kategori, &B.Jenis);

			if(strcasecmp(B.Nama, Nama) == 0){
				break;
			}
		}
	}
	fclose(aksesoris);

	return B;
}

// Fungsi Struct untuk mendapatkan data barang kategori jok pada file sekuensial jok.txt dengan parameter nama barang
Barang getJok(char Nama[]){
	FILE *jok = fopen("jok.txt", "r");
	Barang B;

	if(jok){
		while(!feof(jok)){
			fscanf(jok, "%[^#]#%d#%d#%d#\n", B.Nama, &B.Harga, &B.Kategori, &B.Jenis);

			if(strcasecmp(B.Nama, Nama) == 0){
				break;
			}
		}
	}
	fclose(jok);

	return B;
}

// Fungsi digunakan untuk generate kode pembelian secara acak
void generateKode(char Kode[]){
	int i;

	for(i=0; i<5; i++){
		Kode[i] = (rand()%(90-65))+65;
	}
	Kode[5] = '\0';
}

// Fungsi digunakan untuk mencetak struk belanja
void PrintBelanja(Barang B[], int Size){
	int i, total = 0;
	char Kategori[10], Jenis[9], Kode[6];

	printf("No   Nama Barang                Kategori    Jenis     Harga\n");
	for(i=0; i<Size; i++){
		if(B[i].Kategori == 1){
			strcpy(Kategori, "Mesin");
		}else if(B[i].Kategori == 2){
			strcpy(Kategori, "Ban");
		}else if(B[i].Kategori == 3){
			strcpy(Kategori, "Velg");
		}else if(B[i].Kategori == 4){
			strcpy(Kategori, "Aksesoris");
		}else{
			strcpy(Kategori, "Jok/Kursi");
		}

		if(B[i].Jenis == 1){
			strcpy(Jenis, "Bermotor");
		}else{
			strcpy(Jenis, "Bermobil");
		}

		printf("%-3d  %-25s  %-10s  %-8s  %d\n", i+1, B[i].Nama, Kategori, Jenis, B[i].Harga);

		total += B[i].Harga;
	}
	printf("%-40sTotal Harga : %d\n", " ", total);

	generateKode(Kode);

	printf("\nKode Pemesanan Pembelian : %s\n", Kode);

	printf("\nSerahkan Kode Pembayaran tersebut ke Dealer D'Auto Parts di Alamat Jalan Suka Senja Nomor 69\n");

	printf("\nTerima Kasih Telah Berbelanja di Dealer D'Auto Parts!\n");
}

int main(){
    // variable
	int menu;
	Customer customer;
	Barang barang;

	srand(time(NULL));
	while(true){
		system("cls"); // command untuk clear screen

		// main menu
		printf("===== D'Auto Parts =====\n");
		printf("Jalan Suka Senja Nomor 69\n");
		printf("1 | Masuk\n");
		printf("2 | Daftar Akun\n");
		printf("3 | Keluar\n");
		printf("Pilih Nomor Menu > ");
		scanf("%d", &menu); fflush(stdin);

		printf("\n");

		// kondisi untuk memilih opsi
		if(menu == 1){
			printf("Masuk :\n");
			printf("ID       : ");
			scanf("%[^\n]s", customer.ID); fflush(stdin);
			printf("Password : ");
			scanf("%8[^\n]%*c", customer.Password); fflush(stdin);

			// compare id dengan "dealer", jika kondisi terpenuhi maka akan diarahkan ke menu admin
			if(strcmp(customer.ID, "dealer") == 0 && strcmp(customer.Password, "dealer") == 0){
				printf("\nLogin Sebagai Admin Berhasil!\n\n");
				system("pause");

				// menu admin
				while(true){
					system("cls");
					printf("===== MENU DEALER =====\n");
					printf("1 | Lihat Data Customer\n");
					printf("2 | Hapus Data Customer\n");
					printf("3 | Tambah Barang\n");
					printf("4 | Hapus Barang\n");
					printf("5 | Keluar\n");
					printf("Pilih Menu > ");
					scanf("%d", &menu); fflush(stdin);

					printf("\n");
					if(menu == 1){ // Lihat Data Customer
						printf("Data Customer :\n");
						LihatDataCustomer();
					}else if(menu == 2){ // Hapus Data Customer
						if(IsDataCustomerExist()){
							printf("Data Customer :\n");
							LihatDataCustomer();
							printf("\nMasukkan ID Customer yang akan Dihapus : ");
							scanf("%5[^\n]%*c", customer.ID); fflush(stdin); // input customer id

							if(DeleteDataCustomer(customer.ID)){
								printf("\nHapus Data Customer dengan ID %s Berhasil!\n", customer.ID);
							}else{
								printf("\nHapus Data Customer dengan ID %s Gagal!\n", customer.ID);
							}
						}else{
							printf("Tidak Ada Data Customer!\n");
						}
					}else if(menu == 3){ // Tambah Barang
						printf("Menambahkan Data Barang :\n");
						printf("Masukkan Nama Barang [UNIK]    : ");
						scanf("%25[^\n]%*c", barang.Nama); fflush(stdin); // input nama barang

						printf("Masukkan Harga Barang          : ");
						scanf("%d", &barang.Harga); fflush(stdin); // input harga barang

						printf("Kategori Barang :\n");
						printf("1. Mesin\n");
						printf("2. Ban\n");
						printf("3. Velg\n");
						printf("4. Aksesoris\n");
						printf("5. Jok/Kursi\n");
						while(true){
							printf("Masukkan Nomor Kategori Barang : ");
							scanf("%d", &barang.Kategori); fflush(stdin);

							if(barang.Kategori >= 1 && barang.Kategori <= 5){ // jika menginput diluar inputan maka akan mengulang
								break;
							}
						}

						printf("Jenis Kendaraan :\n");
						printf("1. Bermotor\n");
						printf("2. Bermobil\n");
						while(true){
							printf("Masukkan Nomor Jenis Kendaraan : ");
							scanf("%d", &barang.Jenis); fflush(stdin);

							if(barang.Jenis >= 1 && barang.Jenis <= 2){ // jika inputan salah maka akan mengulang
								break;
							}
						}

						// variabel
						char Kategori[10], Jenis[9];
						if(barang.Kategori == 1){
							strcpy(Kategori, "Mesin");
						}else if(barang.Kategori == 2){
							strcpy(Kategori, "Ban");
						}else if(barang.Kategori == 3){
							strcpy(Kategori, "Velg");
						}else if(barang.Kategori == 4){
							strcpy(Kategori, "Aksesoris");
						}else{
							strcpy(Kategori, "Jok/Kursi");
						}

						if(barang.Jenis == 1){
							strcpy(Jenis, "Bermotor");
						}else{
							strcpy(Jenis, "Bermobil");
						}

						if(TambahBarang(barang)){
							printf("\nBarang %s dengan Harga %d dan Kategori %s Jenis %s Berhasil Ditambahkan!\n", barang.Nama, barang.Harga, Kategori, Jenis);
						}else{
							printf("\nBarang %s dengan Harga %d dan Kategori %s Jenis %s Gagal Ditambahkan!\n", barang.Nama, barang.Harga, Kategori, Jenis);
						}

					}else if(menu == 4){ // Hapus Barang
						printf("Menghapus Data Barang :\n");
						printf("Masukkan Nama Barang : ");
						scanf("%25[^\n]%*c", barang.Nama); fflush(stdin);

						printf("Kategori Barang :\n");
						printf("1. Mesin\n");
						printf("2. Ban\n");
						printf("3. Velg\n");
						printf("4. Aksesoris\n");
						printf("5. Jok/Kursi\n");
						while(true){
							printf("Masukkan Nomor Kategori Barang : ");
							scanf("%d", &barang.Kategori); fflush(stdin);

							if(barang.Kategori >= 1 && barang.Kategori <= 5){ // terus mengulang jika inputan salah
								break;
							}
						}

						// mengisi Kategori[] sesuai inputan user
						char Kategori[10];
						if(barang.Kategori == 1){
							strcpy(Kategori, "Mesin");
						}else if(barang.Kategori == 2){
							strcpy(Kategori, "Ban");
						}else if(barang.Kategori == 3){
							strcpy(Kategori, "Velg");
						}else if(barang.Kategori == 4){
							strcpy(Kategori, "Aksesoris");
						}else{
							strcpy(Kategori, "Jok/Kursi");
						}

						if(HapusBarang(barang)){
							printf("\nBarang %s pada Kategori %s Berhasil Dihapus!\n", barang.Nama, Kategori);
						}else{
							printf("\nBarang %s pada Kategori %s Gagal Dihapus!\n", barang.Nama, Kategori);
						}

					}else if(menu == 5){ // Keluar
						printf("Program Keluar dari Menu Dealer\n");
						break;
					}else{
						printf("Nomor Menu yang Anda Masukkan Tidak Ada!\n");
					}

					system("pause"); // Kembali ke menu awal
				}

            // Login sebagai customers
			}else if(LoginCustomer(customer.ID, customer.Password)){
				printf("\nLogin Berhasil!\n\n");
				system("pause");
				while(true){
					system("cls"); // clear screen command

					//menu customer
					printf("===== MENU CUSTOMER =====\n");
					printf("1 | Cari Barang\n");
					printf("2 | Beli Barang\n");
					printf("3 | Keluar\n");

					printf("Pilih Menu > ");
					scanf("%d", &menu); fflush(stdin); // input pilihan

					printf("\n");
					if(menu == 1){ // Cari Barang
						printf("Pencarian Nama Barang di Kategori Tertentu :\n");
						printf("Masukkan Nama Barang : ");
						scanf("%25[^\n]%*c", barang.Nama); fflush(stdin); // input nama barang

						printf("Kategori Barang :\n");
						printf("1. Mesin\n");
						printf("2. Ban\n");
						printf("3. Velg\n");
						printf("4. Aksesoris\n");
						printf("5. Jok/Kursi\n");
						while(true){
							printf("Masukkan Nomor Kategori Barang : ");
							scanf("%d", &barang.Kategori); fflush(stdin);  // input kategori barang

							if(barang.Kategori >= 1 && barang.Kategori <= 5){ // terus mengulang jika inputan salah
								break;
							}
						}

						printf("\n");
						if(barang.Kategori == 1){
							CariMesin(barang.Nama);
						}else if(barang.Kategori == 2){
							CariBan(barang.Nama);
						}else if(barang.Kategori == 3){
							CariVelg(barang.Nama);
						}else if(barang.Kategori == 4){
							CariAksesoris(barang.Nama);
						}else{
							CariJok(barang.Nama);
						}
					}else if(menu == 2){ // Beli Barang
						int count = 0; // penghitung barang
						Barang cart[10]; //Maksimal Beli Barang 10
						char Jenis[9], loop;

						while(true){
							system("cls"); // clear screen
							printf("Beli Barang [Maksimal 10 Barang] :\n");
							printf("Jumlah Barang : %d\n", count);
							printf("\nMasukkan Nama Barang Secara Lengkap : ");
							scanf("%25[^\n]%*c", barang.Nama); fflush(stdin); // input nama barang

							printf("Kategori Barang :\n");
							printf("1. Mesin\n");
							printf("2. Ban\n");
							printf("3. Velg\n");
							printf("4. Aksesoris\n");
							printf("5. Jok/Kursi\n");
							while(true){
								printf("Masukkan Nomor Kategori Barang : ");
								scanf("%d", &barang.Kategori); fflush(stdin);  // input kategori barang

								if(barang.Kategori >= 1 && barang.Kategori <= 5){ // terus mengulang jika inputan salah
									break;
								}
							}

							printf("\n");
							if(barang.Kategori == 1){ // Mesin
								if(IsMesinExist(barang.Nama)){ // cek barang
									barang = getMesin(barang.Nama);
									cart[count] = barang;
									count += 1;

									if(barang.Jenis == 1){
										strcpy(Jenis, "Bermotor");
									}else{
										strcpy(Jenis, "Bermobil");
									}

									printf("Detail Barang :\n");
									printf("Nama      : %s\n", barang.Nama);
									printf("Harga     : %d\n", barang.Harga);
									printf("Kategori  : Mesin\n");
									printf("Jenis     : %s\n", Jenis);
									printf("\nBerhasil Ditambahkan ke Keranjang!\n");
								}else{
									printf("Gagal Menambahkan Barang ke Keranjang!\n");
								}

							}else if(barang.Kategori == 2){ // Ban
								if(IsBanExist(barang.Nama)){ // cek barang
									barang = getBan(barang.Nama);
									cart[count] = barang;
									count += 1;

									if(barang.Jenis == 1){
										strcpy(Jenis, "Bermotor");
									}else{
										strcpy(Jenis, "Bermobil");
									}

									printf("Detail Barang :\n");
									printf("Nama      : %s\n", barang.Nama);
									printf("Harga     : %d\n", barang.Harga);
									printf("Kategori  : Ban\n");
									printf("Jenis     : %s\n", Jenis);
									printf("\nBerhasil Ditambahkan ke Keranjang!\n");
								}else{
									printf("Gagal Menambahkan Barang ke Keranjang!\n");
								}

							}else if(barang.Kategori == 3){ // Velg
								if(IsVelgExist(barang.Nama)){ // cek barang
									barang = getVelg(barang.Nama);
									cart[count] = barang;
									count += 1;

									if(barang.Jenis == 1){
										strcpy(Jenis, "Bermotor");
									}else{
										strcpy(Jenis, "Bermobil");
									}

									printf("Detail Barang :\n");
									printf("Nama      : %s\n", barang.Nama);
									printf("Harga     : %d\n", barang.Harga);
									printf("Kategori  : Velg\n");
									printf("Jenis     : %s\n", Jenis);
									printf("\nBerhasil Ditambahkan ke Keranjang!\n");
								}else{
									printf("Gagal Menambahkan Barang ke Keranjang!\n");
								}

							}else if(barang.Kategori == 4){ // Aksesoris
								if(IsAksesorisExist(barang.Nama)){ // cek barang
									barang = getAksesoris(barang.Nama);
									cart[count] = barang;
									count += 1;

									if(barang.Jenis == 1){
										strcpy(Jenis, "Bermotor");
									}else{
										strcpy(Jenis, "Bermobil");
									}

									printf("Detail Barang :\n");
									printf("Nama      : %s\n", barang.Nama);
									printf("Harga     : %d\n", barang.Harga);
									printf("Kategori  : Aksesoris\n");
									printf("Jenis     : %s\n", Jenis);
									printf("\nBerhasil Ditambahkan ke Keranjang!\n");
								}else{
									printf("Gagal Menambahkan Barang ke Keranjang!\n");
								}

							}else{ // Jok
								if(IsJokExist(barang.Nama)){ // cek barang
									barang = getJok(barang.Nama);
									cart[count] = barang;
									count += 1;

									if(barang.Jenis == 1){
										strcpy(Jenis, "Bermotor");
									}else{
										strcpy(Jenis, "Bermobil");
									}

									printf("Detail Barang :\n");
									printf("Nama      : %s\n", barang.Nama);
									printf("Harga     : %d\n", barang.Harga);
									printf("Kategori  : Jok/Kursi\n");
									printf("Jenis     : %s\n", Jenis);
									printf("\nBerhasil Ditambahkan ke Keranjang!\n");
								}else{
									printf("Gagal Menambahkan Barang ke Keranjang!\n");
								}

							}

							if(count < 10){ // cek maksimum barang, dan tambah barang untuk dibeli
								while(true){
									printf("Apakah Anda Masih Ingin Beli Barang Lain ? [Y/N] : ");
									scanf("%c", &loop); fflush(stdin);

									if(loop == 'Y' || loop == 'N'){
										break;
									}else{
										printf("\n");
									}
								}

								if(loop == 'N'){
									break;
								}
							}else{
								break;
							}
						}

						if(count > 0){
							system("cls");
							printf("Struk Belanja Barang :\n");
							PrintBelanja(cart, count);
						}else{
							printf("\nBeli Barang Dibatalkan\n");
						}

					}else if(menu == 3){ // Keluar menu customer
						printf("Program Keluar dari Menu Customer\n");
						break;
					}else{
						printf("Nomor Menu yang Anda Masukkan Tidak Ada!\n");
					}

					printf("\n");
					system("pause"); // pause program, kembali ke menu awal
				}
			}else{
				printf("\nID atau Password Salah!\n");
			}
		}else if(menu == 2){ // Daftar Akun
			printf("Mendaftar Akun :\n");
			printf("Masukkan Nama [Maks. 25 Karakter]    : ");
			scanf("%25[^\n]%*c", customer.Nama); fflush(stdin); // input nama

			printf("Masukkan Alamat [Maks. 25 Karakter]  : ");
			scanf("%25[^\n]%*c", customer.Alamat); fflush(stdin); // input alamat

			while(true){
				printf("Masukkan No. Telp. [Maks. 12 Angka]  : ");
				scanf("%12[^\n]%*c", customer.NoTelp); fflush(stdin); // input telepon
				if(isDigit(customer.NoTelp)){
					break;
				}
			}

			printf("Masukkan ID [5 Karakter Tanpa Spasi] : ");
			scanf("%5[^\n]%*c", customer.ID); fflush(stdin); // input id

			printf("Masukkan Password [Maks. 8 Karakter] : ");
			scanf("%8[^\n]%*c", customer.Password); fflush(stdin); // input password

			// Cek daftar customers
			if(DaftarCustomer(customer)){
				printf("\nDaftar Akun dengan ID %s Berhasil\n", customer.ID);
			}else{
				printf("\nDaftar Akun dengan ID %s Gagal\n", customer.ID);
			}
		}else if(menu == 3){ // Keluar Program
			printf("Program selesai, Terima Kasih telah Menggunakan Program Kami :)\n");
			break;
		}else{
			printf("Nomor Menu yang anda masukkan tidak tersedia :(\n");
		}

		printf("\n");
		system("pause"); // Pause program
	}

	return 0; // Program selesai
}
