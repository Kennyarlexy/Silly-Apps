/*
	Dalam game Genshin Impact, terdapat 3 stats utama yang memiliki kontribusi terbesar terhadap damage yang dihasilkan
	suatu karakter, yakni:
	1. Attack
	2. Critical Rate
	3. Critical Damage
	
	Program ini akan mengambil input dari user berupa 3 stats di atas sebanyak dua kali sebagai build 1 
	dan build 2, misalnya:
	
		Build 1:
		1. Attack = 2154
		2. Critical Rate = 65.2%
		3. Critical Damage = 115.7%
	
		Build 2:
		1. Attack = 1973
		2. Critical Rate = 53.6%
		3. Critical Damage = 145.9%
	
	Kemudian program akan menentukan build mana yang akan memberikan overall damage (average damage) terbesar
	serta mencantumkan persentase perbedaan overall damage antara build 1 dan build 2
	misalnya :
	
		"Build 1 lebih baik 15.3% dibandingkan dengan Build 2"
		
	
	*Catatan:
	Karakter yang sudah dibuild dengan baik biasanya memiliki range attack antara 1700-2200, critical rate >= 50%
	dan critical damage >= (critical rate * 2)
	Oleh karena itu, input yang dimasukkan sebaiknya mendekati range tersebut agar lebih realistis.
	Attack selalu integer, critical rate dan critical rate bisa desimal.
*/


#include <iostream>
#include <conio.h>
#include <cmath>

using namespace std;

int main()
{
	cout << "PROGRAM UNTUK MEMBANDINGKAN BUILD\n" << endl;
	char jawaban; //used to check condition when running the loop
	do
	{
		int atk_1, atk_2, em_1, em_2;
		double crate_1, cdmg_1, crate_2, cdmg_2;
		cout << "\nMasukkan stats untuk build 1!" << endl;
		cout << "1. Attack = "; cin >> atk_1;
		cout << "2. Critical Rate(%) = "; cin >> crate_1;
		cout << "3. Critical Damage(%) = "; cin >> cdmg_1;
		cout << "4. Elemental Mastery = "; cin >> em_1;
		
		cout << "\nMasukkan stats untuk build 2!" << endl;
		cout << "1. Attack = "; cin >> atk_2;
		cout << "2. Critical Rate(%) = "; cin >> crate_2;
		cout << "3. Critical Damage(%) = "; cin >> cdmg_2;
		cout << "4. Elemental Mastery = "; cin >> em_2;
		
		double build_1, build_2;
		/*di bawah ini adalah pengaman jika user memasukkan critical rate lebih dari 100% (memang dapat terjadi di 
		dalam game) karena hasil akan meleset*/		
		if (crate_1 > 100) {
			crate_1 = 100;
		}
		if (crate_2 > 100) {
			crate_2 = 100;
		}
		//pengaman selesai
		
		build_1 = atk_1 * ((1 - crate_1 / 100) + (crate_1 / 100 * (1 + cdmg_1 / 100)));
		build_2 = atk_2 * ((1 - crate_2 / 100) + (crate_2 / 100 * (1 + cdmg_2 / 100)));

		double embonus_1, embonus_2;
		embonus_1 = 278.0 * em_1 / (1400 + em_1) / 100;
		embonus_2 = 278.0 * em_2 / (1400 + em_2) / 100;

		double avgreaction_1_vape, avgreaction_1_melt, avgreaction_2_vape, avgreaction_2_melt;
		avgreaction_1_vape = build_1 * (1 + embonus_1 + 0.5);
		avgreaction_2_vape = build_2 * (1 + embonus_2 + 0.5);
		avgreaction_1_melt = build_1 * (1 + embonus_1 + 1);
		avgreaction_2_melt = build_2 * (1 + embonus_2 + 1);

		cout << endl;
		
		double compare;
		if (build_1 > build_2) {
			compare = (build_1 / build_2 - 1) * 100;
			cout << "Build 1 lebih baik " << compare << "% dibandingkan dengan Build 2 (non-reaction)" << endl;
		} else if (build_1 < build_2) {
			compare = (build_2 / build_1 - 1) * 100;
			cout << "Build 2 lebih baik " << compare << "% dibandingkan dengan Build 1 (non-reaction)" << endl;
		} else {
			cout << "Build 1 sama baiknya dengan Build 2 (non-reaction)" << endl;
		}

		double compare_avgreaction_vape, compare_avgreaction_melt;
		if (avgreaction_1_melt > avgreaction_2_melt) {
			compare_avgreaction_vape = (avgreaction_1_vape / avgreaction_2_vape - 1) * 100;
			compare_avgreaction_melt = (avgreaction_1_melt / avgreaction_2_melt - 1) * 100;
			cout << "Build 1 lebih baik " << fmin(compare_avgreaction_vape, compare_avgreaction_melt) << "% - " << fmax(compare_avgreaction_vape, compare_avgreaction_melt) << "% dibandingkan dengan Build 2 (full reaction)" << endl;
		} else if (avgreaction_1_melt < avgreaction_2_melt) {
			compare_avgreaction_vape = (avgreaction_2_vape / avgreaction_1_vape - 1) * 100;
			compare_avgreaction_melt = (avgreaction_2_melt / avgreaction_1_melt - 1) * 100;
			cout << "Build 2 lebih baik " << fmin(compare_avgreaction_vape, compare_avgreaction_melt) << "% - " << fmax(compare_avgreaction_vape, compare_avgreaction_melt) << "% dibandingkan dengan Build 1 (full reaction)" << endl;
		} else {
			cout << "Build 1 sama baiknya dengan Build 2 (full reaction)" << endl;
		}

		double creaction_1_vape, creaction_1_melt, creaction_2_vape, creaction_2_melt;
		creaction_1_vape = atk_1 * (1 + cdmg_1 / 100) * (1 + embonus_1 + 0.5);
		creaction_2_vape = atk_2 * (1 + cdmg_2 / 100) * (1 + embonus_2 + 0.5);
		creaction_1_melt = atk_1 * (1 + cdmg_1 / 100) * (1 + embonus_1 + 1);
		creaction_2_melt = atk_2 * (1 + cdmg_2 / 100) * (1 + embonus_2 + 1);

		double compare_creaction_vape, compare_creaction_melt;
		if (creaction_1_melt > creaction_2_melt) {
			compare_creaction_vape = (creaction_1_vape / creaction_2_vape - 1) * 100;
			compare_creaction_melt = (creaction_1_melt / creaction_2_melt - 1) * 100;
			cout << "Build 1 lebih baik " << fmin(compare_creaction_vape, compare_creaction_melt) << "% - " << fmax(compare_creaction_vape, compare_creaction_melt) << "% dibandingkan dengan Build 2 (crit-only reaction)" << endl;
		} else if (creaction_1_melt < creaction_2_melt) {
			compare_creaction_vape = (creaction_2_vape / creaction_1_vape - 1) * 100;
			compare_creaction_melt = (creaction_2_melt / creaction_1_melt - 1) * 100;
			cout << "Build 2 lebih baik " << fmin(compare_creaction_vape, compare_creaction_melt) << "% - " << fmax(compare_creaction_vape, compare_creaction_melt) << "% dibandingkan dengan Build 1 (crit-only reaction)" << endl;
		} else {
			cout << "Build 1 sama baiknya dengan Build 2 (crit-only reaction)" << endl;
		}

		cout << "\n\nCoba lagi? (y/n)" << endl;
		cin >> jawaban;
	} while (jawaban == 'y');
	cout << "\n\nSilakan tutup program" << endl;
	
	getch();
	
	return 0;
}
