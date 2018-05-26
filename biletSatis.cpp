#include <iostream>
#include<string>
#include<fstream>
#include <sstream>

using namespace std;

void musteriBilgileri();
void koltuklarinDurumu();
void biletSatisIslemi();
void koltukKontrol();
void dosyaKayit();
void biletBilgi();
void biletSistemBilgi();

int kisiSayisi;
int koltukSayisi = 50;
int tutar;
int bos = 0,dolu = 0; // boþ ve dolu koltuk sayýlarý
int koltuklar[50];
int odenecekTutar = 0;
char musteriAdi[50];
// ana fonksiyon
int main(int argc, char** argv) {
    
	cout<<"\t\t\t\tBilet Satis Programi"<<endl;
	cout<<"\t\tGosterim Tarihi 19 Mayis 2018 saat 10:00 dur."<<endl;
	cout<<"\t\tAssagida Koltuklarin Durumlari Yazmaktadir "<<endl;
	cout<<"Bilet Fiyati 10 tl dir, eger siz koltuk numarasini ozel olarak secerseniz her kisi icin arti 3 lira eklenecektir."<<endl;
	
// Koltuklarýn Durumlarý	
	koltuklarinDurumu();
	if(bos>0)
	{
// Musteri Bilgileri
    musteriBilgileri();	
// Bilet satýþ
    biletSatisIslemi();
// Verilerin Dosyaya Kayýt iþlemleri
    dosyaKayit();
// Bilet Bilgi
    biletBilgi();
	}

// Sistemde Kaç adet bilet var
    biletSistemBilgi();
	return 0;
}

void koltuklarinDurumu(){
	int sayac=0;
	int z = 0;
	char koltukNo[50];
	ifstream fin;
    fin.open("bilet.txt", ios::in);
	string line;
	string tutarF;
	string a;

    while(!fin.eof())
	{
	 getline(fin,tutarF);
  	 fin.getline(koltukNo,200);
     getline(fin,a);
	}                 
	
	while (sayac<50) 
	{
		z = sayac + 1;
		if(koltukNo[sayac]=='1')
		{
		  koltuklar[sayac] = 1;
		  cout<<z<<"-dolu"<< ", ";
		  dolu++;
		}
		else
		{
			koltuklar[sayac] = 0;
			cout<<z<<"-bos"<<", ";
        	bos++;
		}
		sayac++;
	}

    istringstream ( tutarF ) >> tutar;
    cout<<" "<<endl;
	fin.close();
}

void musteriBilgileri(){

	cout<<"Adiniz Nedir?"<<endl;
	cin>>musteriAdi;
	cout<< "Kac kisilik yer istiyorsunuz?"<<endl;
	cout<< "Sistemde " << bos <<" kisilik bos koltuk var"<<endl;
	cin>>kisiSayisi;
	while(kisiSayisi>bos)
	{
	   	cout<< "Bu Kadar Bos Yer Yok Tekrar Kisi Sayisi Girin Veya Cikmak Icin '-1' girin?"<<endl;
     	cin>>kisiSayisi;
	}   
}

void biletSatisIslemi(){
	int kontrol;
	int i = 0; // while döngüsü için sayaç
	int koltukNumarasi;
	int a = 0; // kisi sayisini kontrol için 
	cout<<"Koltuk yerlerini kendiniz sececekseniz 1'e basin eger sistem rasgele atamasini istiyorsaniz 0'a basin"<<endl;
	cin>>kontrol;
	while(kontrol !=1 || kontrol != 0)
	{
	if(kontrol==1) {
		cout<<"Koltuk numaralarini girin"<<endl;
		odenecekTutar = kisiSayisi * 13;
		while(i<kisiSayisi)
		{
			cin>>koltukNumarasi;
			if(koltuklar[koltukNumarasi-1] == 0){
				i++;
				koltuklar[koltukNumarasi-1] = 1; 
			} else {
				cout<<"Dolu Koltuk Numarasi Girdiniz Yukaridaki Koltuk Bilgilerinden Kontrol Edin"<<endl;				
			}		
		}
		break;	
	} else if (kontrol == 0) {	
      	odenecekTutar = kisiSayisi * 10;	
		while(i<koltukSayisi && a<kisiSayisi)
		{
			if(koltuklar[i]==0)
			{
				koltuklar[i]=1;
				a++;
			}
			i++;
		}
		break;
	} else {
		cout<<"Yanlis Secim Yaptiniz Tekrar Deneyin"<<endl;
		cin>>kontrol;
	}
 }	
}

void dosyaKayit() {
	tutar+=odenecekTutar;
   	ofstream fout("bilet.txt",std::ios::app);
 	fout <<"Kisi Sayisi= "<< kisiSayisi<<endl;
	fout <<"Musteri Adi= "<< musteriAdi<<endl;
	fout << "Odenecek Tutar: "<< odenecekTutar<<endl;
	fout << "-------"<<endl;
	fout <<tutar<<endl;
	fout.close();	

   ofstream f;
   f.open("bilet.txt",std::ios::app);
   for(int i = 0; i < 50; i++)
    {
    	if(koltuklar[i] == 1)
    	 f.put('1');
    	else
    	 f.put('0');
	}
     f<<endl;
	 f.close();
	
}

void biletBilgi() {
	cout<<"Gosterim Tarihi 19 Mayis 2018 saat 10:00 dur."<<endl;
	cout<<"Bilet Sahibininin Ismi: "<< musteriAdi<<endl;
	cout<<"Bilet Sayisi: "<<kisiSayisi<<endl;
	cout<<"Ödenecek Tutar: "<< odenecekTutar<<endl;
}

void biletSistemBilgi() {
	
	if(kisiSayisi==bos)
	{
	  cout<<"Biletler Tukenmistir"<<endl;
	  cout<<"Biletlerin Toplam Geliri= "<<tutar<<" tl dir."<<endl;
	}
	else
	{
		cout<<"Sistemde Toplamda "<<bos-kisiSayisi<<" adet koltuk vardýr"<<endl;
		cout<<"Su ana kadar biletlerin toplam geliri "<<tutar<<" tl dir."<<endl;
	}
	  
}


