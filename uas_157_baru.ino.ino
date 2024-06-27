#include <LiquidCrystal.h> //untuk library LCD
LiquidCrystal lcd(11,10,9,8,7,6); // parameternya dari kabel yg masuk ke arduino

int gas = 0; // buat variabel untuk gas 
int greenLed = 1; // buat variabel untuk led hijau dengan indikator 1
int yellowLed = 2; // buat variabel untuk led kuning dengan indikator 2
int redLed = 3; // buat variabel untuk led merah dengan indikator 3
int speaker = 4; // buat variabel untuk speaker dengan indikator 4
int flame = 5; // buat variabel untuk flame sensor dengan indikator 5

void setup() {
  // set up kode untuk mendefinisikan peran masing2 variabel
  lcd.begin(16, 2);
  pinMode (gas, INPUT);
  pinMode (flame, INPUT);
  pinMode (greenLed, OUTPUT);
  pinMode (yellowLed, OUTPUT);
  pinMode (redLed, OUTPUT);
  pinMode (speaker, OUTPUT);

  // inisial serial monitor
  Serial.begin(9600);

  // menampilkan identitas
  lcd.setCursor(0, 0);
  lcd.print("adam sulton");
  lcd.setCursor(0, 1);
  lcd.print("1462100157");
  delay(2000); // Tampilkan selama 2 detik sebelum memulai loop
  lcd.clear();
}

void loop() {

  // baca aturan sensor
  int gasStatus = digitalRead(gas);
  int flameStatus = digitalRead(flame);

  // cetak status sensor ke serial monitor
  Serial.print("Gas : ");
  Serial.print(gasStatus);
  Serial.print("Flame : ");
  Serial.print(flameStatus);


  // logika aturan sistem

  // situasi tidak ada gas atau api yang terdeteksi. Hanya indikator netral (hijau) yang menyala.
  if (gasStatus == LOW && flameStatus == LOW) { 
  // Jika sensor gas dan flame tidak mendeteksi gas dan api
    lcd.setCursor(2, 0); lcd.print("Gas & Flame"); 
  // Tampilkan "Gas & Flame" di baris pertama LCD, mulai dari kolom ke-2
    lcd.setCursor(2, 1); lcd.print("Tidak Terdeteksi"); 
  // Tampilkan "Not Detected" di baris kedua LCD, mulai dari kolom ke-2
    digitalWrite(greenLed, HIGH); // Nyalakan LED hijau (netral)
    digitalWrite(yellowLed, LOW); // Matikan LED kuning (indikator gas)
    digitalWrite(redLed, LOW); // Matikan LED merah (indikator api)
    digitalWrite(speaker, LOW); // Matikan speaker
  }
  
  // situasi hanya sensor gas yang mendeteksi gas. Hanya indikator gas dan suara yang menyala.
  else if (gasStatus == HIGH && flameStatus == LOW) { 
  // Jika sensor gas mendeteksi keberadaan gas tapi sensor flame tidak mendeteksi api
    lcd.setCursor(2, 0); lcd.print("Gas Terdeteksi"); 
  // Tampilkan "Gas Detected" di baris pertama LCD, mulai dari kolom ke-2
    digitalWrite(greenLed, LOW); // Matikan LED hijau (netral)
    digitalWrite(yellowLed, HIGH); // Nyalakan LED kuning (indikator gas)
    digitalWrite(redLed, LOW); // Matikan LED merah (indikator api)
    digitalWrite(speaker, HIGH); // Nyalakan speaker (indikator suara)
    delay(200); // Tunggu selama 200 milidetik
    digitalWrite(speaker, LOW); // Matikan speaker
  }
  
  // situasi hanya sensor flame yang mendeteksi api. Hanya indikator api dan suara yang menyala.
  else if (gasStatus == LOW && flameStatus == HIGH) { 
    // Jika sensor gas tidak mendeteksi gas tapi sensor flame mendeteksi api
    lcd.setCursor(1, 0); lcd.print("Flame Detected"); 
  // Tampilkan "Flame Detected" di baris pertama LCD, mulai dari kolom ke-1
    digitalWrite(greenLed, LOW); // Matikan LED hijau (netral)
    digitalWrite(yellowLed, LOW); // Matikan LED kuning (indikator gas)
    digitalWrite(redLed, HIGH); // Nyalakan LED merah (indikator api)
    digitalWrite(speaker, HIGH); // Nyalakan speaker (indikator suara)
    delay(200); // Tunggu selama 200 milidetik
    digitalWrite(speaker, LOW); // Matikan speaker
  } 
  
  // blok if 1 : mendeteksi sensor gas dan flame. semua indikator menyala
  else if (gasStatus == HIGH && flameStatus == HIGH) { 
  // Jika sensor gas dan flame mendeteksi keberadaan gas dan api
    lcd.setCursor(2, 0); lcd.print("Gas & Flame"); 
  // Tampilkan "Gas & Flame" di baris pertama LCD, mulai dari kolom ke-2
    lcd.setCursor(4, 1); lcd.print("Terdeteksi"); 
  // Tampilkan "terdeteksi" di baris kedua LCD, mulai dari kolom ke-4
    digitalWrite(greenLed, LOW); // Matikan LED hijau (netral)
    digitalWrite(yellowLed, HIGH); // Nyalakan LED kuning (indikator gas)
    digitalWrite(redLed, HIGH); // Nyalakan LED merah (indikator api)
    digitalWrite(speaker, HIGH); // Nyalakan speaker (indikator suara)
  } 

  delay(300);
  lcd.clear();
}

