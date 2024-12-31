#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char name[50];
    int sut;       
    int pas;       
    int hiz;       
    int teknik;    
    int defans;    
} Team;
void on_save_player_button_clicked(GtkButton *button, gpointer user_data);//kaydetme fonksiyonu
void on_save_player_button1_clicked(GtkButton *button, gpointer user_data);//kaydetme fonksiyonu
int load_teams(const char *filename, Team teams[], int max_teams);//dosyadan takimlari yükleme fonksiyonu
Team *find_team(const char *name, Team teams[], int team_count);//secilen takimin hangi takim olduğunu pointer olarak döndüren fonksiyon
void simulate_match(const Team *team1, const Team *team2, GtkLabel *label_result);//simülasyon
void on_buton1_clicked(GtkButton *button, gpointer user_data);//buton1 tıklama fonksiyonu
void on_buton2_clicked(GtkButton *button, gpointer user_data);//buton2 tıklama fonksiyonu
void on_buton3_clicked(GtkButton *button, gpointer user_data);//buton3 tıklama fonksiyonu
void combo(GtkComboBoxText *combo1, GtkComboBoxText *combo2,GtkBuilder *builder);// comboboxların içini dolduran fonksiyon
gboolean on_istatistik_window_gizleme_event(GtkWidget *widget, GdkEvent *event, gpointer user_data);//Pencereyi yok etmek yerine gizlemek için geri çağırma fonksiyonu
int main(int argc, char *argv[]) {
    GtkWidget *window;//<----- ana pencere için widget atıyoruz
    GtkBuilder *builder;//<----- ara yüz için widget atıyoruz
    GtkComboBoxText *combo1, *combo2;//<----- takimlari seçeceğimiz kutucuklar için değişken atıyoruz
    GtkWidget *entry_player0;//<----- kullanıcıdan giriş almak için değişken atıyoruz(dream team)
    GtkWidget *entry_player1;//<----- kullanıcıdan giriş almak için değişken atıyoruz(dream team)
    GtkWidget *entry_player2;//<----- kullanıcıdan giriş almak için değişken atıyoruz(dream team)
    GtkWidget *entry_player3;//<----- kullanıcıdan giriş almak için değişken atıyoruz(dream team)
    GtkWidget *entry_player4;//<----- kullanıcıdan giriş almak için değişken atıyoruz(dream team)
    GtkWidget *save_player_button;//<----- kullanıcının bu girişleri kaydeteceği buton için değişken atıyoruz(dream team)
    GtkWidget *entry_player5;//<----- kullanıcıdan giriş almak için değişken atıyoruz(dream team2)
    GtkWidget *entry_player6;//<----- kullanıcıdan giriş almak için değişken atıyoruz(dream team2)
    GtkWidget *entry_player7;//<----- kullanıcıdan giriş almak için değişken atıyoruz(dream team2)
    GtkWidget *entry_player8;//<----- kullanıcıdan giriş almak için değişken atıyoruz(dream team2)
    GtkWidget *entry_player9;//<----- kullanıcıdan giriş almak için değişken atıyoruz(dream team2)
    GtkWidget *save_player_button1;//<----- kullanıcının bu girişleri kaydeteceği buton için değişken atıyoruz(dream team2)
    


    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("futbol_son.glade");//<------ arayüzü değişkene tanımlıyoruz
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));//<----- ana pencereyi değişkene atıyoruz
    combo(combo1,combo2,builder);//<---- takimlari seciceğimiz secme kutusunun içine takimlari yazdiran fonksiyonu çağrıyor
    
    entry_player0 = GTK_WIDGET(gtk_builder_get_object(builder, "entry_player0"));//<------ arayüzde ki entrylere bağladım(istatisik_window)
    entry_player1 = GTK_WIDGET(gtk_builder_get_object(builder, "entry_player1"));//<------ arayüzde ki entrylere bağladım(istatisik_window)
    entry_player2 = GTK_WIDGET(gtk_builder_get_object(builder, "entry_player2"));//<------ arayüzde ki entrylere bağladım(istatisik_window)
    entry_player3 = GTK_WIDGET(gtk_builder_get_object(builder, "entry_player3"));//<------ arayüzde ki entrylere bağladım(istatisik_window)
    entry_player4 = GTK_WIDGET(gtk_builder_get_object(builder, "entry_player4"));//<------ arayüzde ki entrylere bağladım(istatisik_window)
    save_player_button = GTK_WIDGET(gtk_builder_get_object(builder, "save_player_button"));//<------- ara yüzde ki save tuşu(istatisik_window)
    
    entry_player5 = GTK_WIDGET(gtk_builder_get_object(builder, "entry_player5"));//<------ arayüzde ki entrylere bağladım(istatisik_window2)
    entry_player6 = GTK_WIDGET(gtk_builder_get_object(builder, "entry_player6"));//<------ arayüzde ki entrylere bağladım(istatisik_window2)
    entry_player7 = GTK_WIDGET(gtk_builder_get_object(builder, "entry_player7"));//<------ arayüzde ki entrylere bağladım(istatisik_window2)
    entry_player8 = GTK_WIDGET(gtk_builder_get_object(builder, "entry_player8"));//<------ arayüzde ki entrylere bağladım(istatisik_window2)
    entry_player9 = GTK_WIDGET(gtk_builder_get_object(builder, "entry_player9"));//<------ arayüzde ki entrylere bağladım(istatisik_window2)
    save_player_button1 = GTK_WIDGET(gtk_builder_get_object(builder, "save_player_button1"));//<------- ara yüzde ki save tuşu(istatisik_window2)


    //entries dizisi
    GtkEntry *entries[10] = { 
    GTK_ENTRY(entry_player0), 
    GTK_ENTRY(entry_player1), 
    GTK_ENTRY(entry_player2), 
    GTK_ENTRY(entry_player3), 
    GTK_ENTRY(entry_player4),
    GTK_ENTRY(entry_player5), 
    GTK_ENTRY(entry_player6), 
    GTK_ENTRY(entry_player7), 
    GTK_ENTRY(entry_player8), 
    GTK_ENTRY(entry_player9)      
                            };
    
    //buton tanımlama
    GtkButton *buton1 = GTK_BUTTON(gtk_builder_get_object(builder, "buton1"));//<----- butonları tanımlama
    GtkButton *buton2 = GTK_BUTTON(gtk_builder_get_object(builder, "buton2"));//<----- butonları tanımlama
    GtkButton *buton3 = GTK_BUTTON(gtk_builder_get_object(builder, "buton3"));//<----- butonları tanımlama
    GtkWidget *istatistik_window = GTK_WIDGET(gtk_builder_get_object(builder, "istatistik_window"));//<---- dream team save için arayüz
    GtkWidget *istatistik_window2 = GTK_WIDGET(gtk_builder_get_object(builder, "istatistik_window2"));//<---- dream team2 save için arayüz
    //sinyal bağlama
    g_signal_connect(save_player_button, "clicked", G_CALLBACK(on_save_player_button_clicked), entries);//<----- basılma sinyalini save fonksiyonunu bağlama
    g_signal_connect(save_player_button1, "clicked", G_CALLBACK(on_save_player_button1_clicked), entries);//<----- basılma sinyalini save fonksiyonunu bağlama
    g_signal_connect(buton1, "clicked", G_CALLBACK(on_buton1_clicked), builder);//<----- butonlara tıklama sinyalini fonksiyonlara bağlama
    g_signal_connect(buton2, "clicked", G_CALLBACK(on_buton2_clicked), builder);//<----- butonlara tıklama sinyalini fonksiyonlara bağlama
    g_signal_connect(buton3, "clicked", G_CALLBACK(on_buton3_clicked), builder);//<----- butonlara tıklama sinyalini fonksiyonlara bağlama
    g_signal_connect(istatistik_window, "delete-event", G_CALLBACK(on_istatistik_window_gizleme_event), NULL);//<------ çarpıya basıldığında kodu bitiren sinyal bağlantısı(dream team)
    g_signal_connect(istatistik_window2, "delete-event", G_CALLBACK(on_istatistik_window_gizleme_event), NULL);//<------ çarpıya basıldığında kodu bitiren sinyal bağlantısı(dream team2)
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);//<------ çarpıya basıldığında kodu bitiren sinyal bağlantısı
    gtk_widget_show_all(window);//<---- ana arayüzün gözükmesi için çağrılan fonksiyon
    gtk_main();

    return 0;
}
//kaydetme fonksiyonları
void on_save_player_button_clicked(GtkButton *button, gpointer user_data) {
    GtkEntry **entries = (GtkEntry **)user_data;

    // Entry'lerden tam sayı al ve 100 ile modunu hesapla
    for (int i = 0; i < 5; i++) {
        const gchar *text = gtk_entry_get_text(entries[i]); // Kullanıcının girdiği metni al
        if (g_ascii_isdigit(*text) || (*text == '-' && g_ascii_isdigit(*(text + 1)))) {
            int value = atoi(text); // Metni tam sayıya çevir
            g_print("Player %d: %d mod 100 = %d\n", i, value, value % 100);
            // Entry widget'lerinden değerleri al
    const char *sut = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const char *pas = gtk_entry_get_text(GTK_ENTRY(entries[1]));
    const char *hiz = gtk_entry_get_text(GTK_ENTRY(entries[2]));
    const char *teknik = gtk_entry_get_text(GTK_ENTRY(entries[3]));
    const char *defans = gtk_entry_get_text(GTK_ENTRY(entries[4]));

    // Takım bilgilerini güncelle
    
    // Dosyaya ekleme yapma kısmı
    FILE *file = fopen("takimlar2.txt", "w");  // Dosyayı ekleme (append) modunda açıyoruz
    if (file == NULL) {
        g_print("Dosya açılamadı.\n");
        return;
    }
    
    // Takım bilgilerini belirli formatta dosyaya ekliyoruz
    fprintf(file, "Dream Team: Sut=%s, Pas=%s, Hiz=%s, Teknik=%s, Defans=%s\n"
    , sut, pas, hiz, teknik,defans);
    
    fclose(file);  // Dosyayı kapatıyoruz
    g_print("Yeni takım  dosyaya eklendi.\n");
        } else {
            g_print("Player %d: Geçersiz bir sayı girdiniz!\n", i);
        }
    }
}
void on_save_player_button1_clicked(GtkButton *button, gpointer user_data) {
    GtkEntry **entries = (GtkEntry **)user_data;

    // Entry'lerden tam sayı al ve 100 ile modunu hesapla
    for (int i = 5; i < 10; i++) {
        const gchar *text = gtk_entry_get_text(entries[i]); // Kullanıcının girdiği metni al
        if (g_ascii_isdigit(*text) || (*text == '-' && g_ascii_isdigit(*(text + 1)))) {
            int value = atoi(text); // Metni tam sayıya çevir
            g_print("Player %d: %d mod 100 = %d\n", i, value, value % 100);
            // Entry widget'lerinden değerleri al
    const char *sut = gtk_entry_get_text(GTK_ENTRY(entries[5]));
    const char *pas = gtk_entry_get_text(GTK_ENTRY(entries[6]));
    const char *hiz = gtk_entry_get_text(GTK_ENTRY(entries[7]));
    const char *teknik = gtk_entry_get_text(GTK_ENTRY(entries[8]));
    const char *defans = gtk_entry_get_text(GTK_ENTRY(entries[9]));

    // Takım bilgilerini güncelle
    
    // Dosyaya ekleme yapma kısmı
    FILE *file = fopen("takimlar3.txt", "w");  // Dosyayı ekleme (append) modunda açıyoruz
    if (file == NULL) {
        g_print("Dosya açılamadı.\n");
        return;
    }
    
    // Takım bilgilerini belirli formatta dosyaya ekliyoruz
    fprintf(file, "Dream Team2: Sut=%s, Pas=%s, Hiz=%s, Teknik=%s, Defans=%s\n"
    , sut, pas, hiz, teknik,defans);
    
    fclose(file);  // Dosyayı kapatıyoruz
    g_print("Yeni takım2  dosyaya eklendi.\n");
        } else {
            g_print("Player %d: Geçersiz bir sayı girdiniz!\n", i);
        }
    }
}
// Dosyadan takımları yükleyen fonksiyon
int load_teams(const char *filename, Team teams[], int max_teams) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Dosya açılamadı");
        return -1;
    }



    int count = 0;
    char line[256];
    while (fgets(line, sizeof(line), file) && count < max_teams) {
       if (sscanf(line, "%[^:]: Sut=%d, Pas=%d, Hiz=%d, Teknik=%d, Defans=%d",
           teams[count].name, &teams[count].sut, &teams[count].pas,
           &teams[count].hiz, &teams[count].teknik, &teams[count].defans) == 6) {
    count++;
} 

    } if (sscanf(line, "%[^:]: Şut=%d, Pas=%d, Hiz=%d, Teknik=%d, Defans=%d",
                   teams[count].name, &teams[count].sut, &teams[count].pas,
                   &teams[count].hiz, &teams[count].teknik, &teams[count].defans) == 6) {
            count++;
        } 

    fclose(file);
    return count;
}
// load_teams de Teams[] de ki takimlari tek tek deniyor eğer düzgün takimi bulursa bunu pointer olarak döndürüyor
Team *find_team(const char *name, Team teams[], int team_count) {
    for (int i = 0; i < team_count; i++) {
        if (strcasecmp(teams[i].name, name) == 0) {
            return &teams[i];
        }
    }
    return NULL;
}
// Simüle etme fonksiyonu
void simulate_match(const Team *team1, const Team *team2, GtkLabel *label_result) {
    int team1_score = 0, team2_score = 0;
    int atak1;
    int atak2;
    int team1_shooting = team1->sut;
    int team1_technical = team1->teknik;
    int team2_shooting = team2->sut;
    int team2_technical = team2->teknik;

    int team1_defending = team1->defans;
    int team2_defending = team2->defans;

    int team1_sprint = team1->hiz;
    int team2_sprint = team2->hiz;

    int team1_pases = team1->pas;
    int team2_pases = team2->pas;
    
  
    if (team1_sprint>team2_sprint+30)
    {
        atak1=7;
        atak2=20;
    }
    else if (team1_sprint>team2_sprint+20)
    {
        atak1=8;
        atak2=15;
    }
    else if (team1_sprint>team2_sprint+10)
    {
        atak1=8;
        atak2=10;
    }
    else if (team1_sprint>team2_sprint)
    {
        atak1=10;
        atak2=10;
    }
    else if (team2_sprint>team1_sprint+30)
    {
        atak2=7;
        atak1=20;
    }
    else if (team2_sprint>team1_sprint+20)
    {
        atak2=8;
        atak1=15;
    }
    else if (team2_sprint>team1_sprint+10)
    {
        atak2=8;
        atak1=10;
    }
    else if (team2_sprint>team1_sprint)
    {
        atak2=10;
        atak1=10;
    }
    
    

    
    int team1_power = (team1_shooting / 5 + team1_technical*0.3+team1_pases*0.3+team1_sprint/5); 
    int team2_power = (team2_shooting / 5 + team2_technical*0.3+team2_pases*0.3+team2_sprint/5); 
    int mutlak_power=abs(team1_power-team2_power);

   
    if (team1_power>team2_power+90)
    {
    team1_power-=(team2_defending*10)/10;
    team2_power-=(team1_defending*10)/15;
       if (team2_power<=0)
    {
        team2_power=mutlak_power-65;
    }
    
    }
    else if (team1_power>team2_power+80)
    {
    team1_power-=(team2_defending*10)/10;
    team2_power-=(team1_defending*10)/15;
       if (team2_power<=0)
    {
        team2_power=mutlak_power-55;
    }
    
    }
    else if (team1_power>team2_power+70)
    {
    team1_power-=(team2_defending*10)/10;
    team2_power-=(team1_defending*10)/15;
       if (team2_power<=0)
    {
        team2_power=mutlak_power-45;
    }
    
    }
    else if (team1_power>team2_power+60)
    {
    team1_power-=(team2_defending*10)/10;
    team2_power-=(team1_defending*10)/15;
       if (team2_power<=0)
    {
        team2_power=mutlak_power-35;
    }
    
    }
    else if (team1_power>team2_power+50)
    {
    team1_power-=(team2_defending*10)/10;
    team2_power-=(team1_defending*10)/15;
       if (team2_power<=0)
    {
        team2_power=mutlak_power-25;
    }
    
    }
    else if (team1_power>team2_power+40)
    {
    team1_power-=(team2_defending*10)/10;
    team2_power-=(team1_defending*10)/15;
       if (team2_power<=0)
    {
        team2_power=mutlak_power-15;
    }
    
    }
    else if (team1_power>team2_power+30)
    {
    team1_power-=(team2_defending*10)/10;
    team2_power-=(team1_defending*10)/15;
       if (team2_power<=0)
    {
        team2_power=mutlak_power-5;
    }
    
    }
    else if (team1_power>team2_power+20)
    {
    team1_power-=(team2_defending*10)/10;
    team2_power-=(team1_defending*10)/14;
    if (team2_power<=0)
    {
        team2_power=mutlak_power;
    }   
    }
    else if (team1_power>team2_power+10)
    {
    team1_power-=(team2_defending*10)/11;
    team2_power-=(team1_defending*10)/13;
    if (team2_power<=0)
    {
        team2_power=mutlak_power;
    }   
    }
    else if (team1_power>team2_power)
    {
    team1_power-=(team2_defending*10)/12;
    team2_power-=(team1_defending*10)/12;
    }


    if (team2_power>team1_power+90)
    {
    team1_power-=(team2_defending*10)/15;
    team2_power-=(team1_defending*10)/11;
    if (team1_power<=0)
    {
        team1_power=mutlak_power-65;
    }
      
    }
    else if (team2_power>team1_power+80)
    {
    team1_power-=(team2_defending*10)/15;
    team2_power-=(team1_defending*10)/11;
    if (team1_power<=0)
    {
        team1_power=mutlak_power-55;
    }
      
    }
    else if (team2_power>team1_power+70)
    {
    team1_power-=(team2_defending*10)/15;
    team2_power-=(team1_defending*10)/11;
    if (team1_power<=0)
    {
        team1_power=mutlak_power-45;
    }
      
    }
    else if (team2_power>team1_power+60)
    {
    team1_power-=(team2_defending*10)/15;
    team2_power-=(team1_defending*10)/11;
    if (team1_power<=0)
    {
        team1_power=mutlak_power-35;111111111111
    }
      
    }
    else if (team2_power>team1_power+50)
    {
    team1_power-=(team2_defending*10)/15;
    team2_power-=(team1_defending*10)/11;
    if (team1_power<=0)
    {
        team1_power=mutlak_power-25;
    }
      
    }
    else if (team2_power>team1_power+40)
    {
    team1_power-=(team2_defending*10)/15;
    team2_power-=(team1_defending*10)/11;
    if (team1_power<=0)
    {
        team1_power=mutlak_power-15;
    }
      
    }
    else if (team2_power>team1_power+30)
    {
    team1_power-=(team2_defending*10)/15;
    team2_power-=(team1_defending*10)/11;
    if (team1_power<=0)
    {
        team1_power=mutlak_power-5;
    }
      
    }
    
    else if (team2_power>team1_power+20)
    {
    team1_power-=(team2_defending*10)/14;
    team2_power-=(team1_defending*10)/10;
    if (team1_power<=0)
    {
        team1_power=mutlak_power;
    }   
    }
    else if (team2_power>team1_power+10)
    {
    team1_power-=(team2_defending*10)/13;
    team2_power-=(team1_defending*10)/11;
    if (team1_power<=0)
    {
        team1_power=mutlak_power;
    }
    }
    else if (team2_power>team1_power)
    {
    team1_power-=(team2_defending*10)/12;
    team2_power-=(team1_defending*10)/12;
    }
   
   if (team1_power==team2_power)
   {
    team1_power-=(team2_defending*10)/12;
    team2_power-=(team1_defending*10)/12;
   }
   
    
    
    
    
    
    


    // Şans hesaplamaları
   
    int team1_chance = team1_power;
    int team2_chance = team2_power;

    
    for (int i = 0; i < 95; i+=atak1) { 
        int random_value = rand() % 100;

        // Takım 2'nin gol şansı
        if (random_value < team1_chance) {
            team1_score++;
        }
        switch (team1_score)
        {
        case 1:
            team1_chance-=5;
            break;
        case 2:
            team1_chance-=10;
            break;
        case 3:
            team1_chance-=20;
            break;    
        case 4:
            team1_chance-=20;
            break;
        case 5:
            team1_chance-=10;
            break;
        default:
            break;
        }
    }
      for (int i = 0; i < 95; i+=atak2) { 
        int random_value = rand() % 100;

        // Takım 2'nin gol şansı
        if (random_value < team2_chance) {
            team2_score++;
        }
        switch (team2_score)
        {
        case 1:
            team2_chance-=5;
            break;
        case 2:
            team2_chance-=10;
            break;
        case 3:
            team2_chance-=20;
            break;    
        case 4:
            team2_chance-=20;
            break;
        case 5:
            team2_chance-=10;
            break;
        default:
            break;
        }
    }

    // skoru ve kazananı ekrana yazdır
    char result_text[256];
    if (team1_score > team2_score) {
        snprintf(result_text, sizeof(result_text), "%s \nkazandi! (Skor: %d - %d)", team1->name, team1_score, team2_score);
    } else if (team2_score > team1_score) {
        snprintf(result_text, sizeof(result_text), "%s \nkazandi! (Skor: %d - %d)", team2->name, team2_score, team1_score);
    } else {
        snprintf(result_text, sizeof(result_text), "Beraberlik! (Skor: %d - %d)", team1_score, team2_score);
    }

    // Sonucu etikete yazdır
    gtk_label_set_text(label_result, result_text);
}
//Pencereyi yok etmek yerine gizlemek için geri çağırma fonksiyonu
gboolean on_istatistik_window_gizleme_event(GtkWidget *widget, GdkEvent *event, gpointer user_data) {
    gtk_widget_hide(widget); // Pencereyi gizle
    return TRUE; // TRUE döndürerek varsayılan yok etme davranışını engelle
}
//dream team'in değerlerini değistirmek için buton1 e basılınca çağrılacak fonksiyon
void on_buton1_clicked(GtkButton *button, gpointer user_data) {
    GtkBuilder *builder = GTK_BUILDER(user_data);
    GtkWidget *istatistik_window;

    istatistik_window = GTK_WIDGET(gtk_builder_get_object(builder, "istatistik_window"));

    if (istatistik_window) {
        gtk_widget_show_all(istatistik_window); // Pencereyi göster
    } else {
        g_print("İstatistik penceresi bulunamadi!\n");
    }
    gtk_widget_show_all(istatistik_window);
}
//dream team2'in değerlerini değistirmek için buton2 e basılınca çağrılacak fonksiyon
void on_buton2_clicked(GtkButton *button, gpointer user_data) {
    GtkBuilder *builder = GTK_BUILDER(user_data);
    GtkWidget *istatistik_window2;

    istatistik_window2 = GTK_WIDGET(gtk_builder_get_object(builder, "istatistik_window2"));

    if (istatistik_window2) {
        gtk_widget_show_all(istatistik_window2); // Pencereyi göster
    } else {
        g_print("İstatistik penceresi bulunamadi!\n");
    }
    gtk_widget_show_all(istatistik_window2);
}
//simile etme işleminin yapılması için basılan buton3 fonksiyonu
void on_buton3_clicked(GtkButton *button, gpointer user_data) {
    GtkBuilder *builder = GTK_BUILDER(user_data);
    GtkComboBoxText *combo1, *combo2;
    GtkLabel *label_result;
    const char *team1_name, *team2_name;

    combo1 = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_team1"));
    combo2 = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_team2"));
    label_result = GTK_LABEL(gtk_builder_get_object(builder, "label_result"));

    team1_name = gtk_combo_box_text_get_active_text(combo1);
    team2_name = gtk_combo_box_text_get_active_text(combo2);

    if (team1_name && team2_name) {
        Team teams1[25], teams2[25],teams3[25]; // İki farklı dosya için ayrı diziler
        int team1_count = load_teams("takimlar.txt", teams1, 22);
        int team2_count = load_teams("takimlar2.txt", teams2, 2);
        int team3_count = load_teams("takimlar3.txt", teams3, 2);

        Team *team1 = NULL;
        Team *team2 = NULL;

        // Eğer Dream Team seçildiyse, sadece takimlar2.txt dosyasından oku
        if (strcasecmp(team1_name, "Dream Team") == 0) {
            team1 = find_team(team1_name, teams2, team2_count);
        }else if (strcasecmp(team1_name, "Dream Team2") == 0)
        {
            team1 = find_team(team1_name, teams3, team3_count);
        }
        
         else {
            team1 = find_team(team1_name, teams1, team1_count);
        }
        ////////////////////////////////////
        if (strcasecmp(team2_name, "Dream Team") == 0) {
            team2 = find_team(team2_name, teams2, team2_count);
        }
        else if (strcasecmp(team2_name, "Dream Team2") == 0)
        {
            team2 = find_team(team2_name, teams3, team3_count);
        }
         
        else {
            team2 = find_team(team2_name, teams1, team1_count);
        }
        ////////////////////////////////////
        if (team1 && team2) {
            simulate_match(team1, team2, label_result);
        } else {
            gtk_label_set_text(label_result, "Takım özellikleri bulunamadı.");
        }
    } else {
        gtk_label_set_text(label_result, "Lütfen her iki \ntakımı da seçin.");
    }
}
//comboboxları doldurma fonksiyonu
void combo(GtkComboBoxText *combo1, GtkComboBoxText *combo2,GtkBuilder *builder)
{
    combo1 = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_team1"));
    combo2 = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_team2"));

    gtk_combo_box_text_append_text(combo1, "Dream team");
    gtk_combo_box_text_append_text(combo1, "Dream team2");
    gtk_combo_box_text_append_text(combo1, "Manchester City");
    gtk_combo_box_text_append_text(combo1, "Manchester United");
    gtk_combo_box_text_append_text(combo1, "Chelsea");
    gtk_combo_box_text_append_text(combo1, "Arsenal");
    gtk_combo_box_text_append_text(combo1, "Nothingam Forest");
    gtk_combo_box_text_append_text(combo1, "bournemounth");
    gtk_combo_box_text_append_text(combo1, "Aston Villa");
    gtk_combo_box_text_append_text(combo1, "Fullham");
    gtk_combo_box_text_append_text(combo1, "Brighton");
    gtk_combo_box_text_append_text(combo1, "Tottenhem");
    gtk_combo_box_text_append_text(combo1, "Liverpool");
    gtk_combo_box_text_append_text(combo1, "Brentford");
    gtk_combo_box_text_append_text(combo1, "Newcastle United");
    gtk_combo_box_text_append_text(combo1, "Westham United");
    gtk_combo_box_text_append_text(combo1, "Crystal Palace");
    gtk_combo_box_text_append_text(combo1, "Everton");
    gtk_combo_box_text_append_text(combo1, "Leicester City");
    gtk_combo_box_text_append_text(combo1, "Wolverhempton");
    gtk_combo_box_text_append_text(combo1, "Ipswhich");
    gtk_combo_box_text_append_text(combo1, "Southampton");
    


    

    gtk_combo_box_text_append_text(combo2, "Dream team");
    gtk_combo_box_text_append_text(combo2, "Dream team2");
    gtk_combo_box_text_append_text(combo2, "Manchester City");
    gtk_combo_box_text_append_text(combo2, "Manchester United");
    gtk_combo_box_text_append_text(combo2, "Aston Villa");
    gtk_combo_box_text_append_text(combo2, "Fullham");
    gtk_combo_box_text_append_text(combo2, "Brighton");
    gtk_combo_box_text_append_text(combo2, "Nothingam Forest");
    gtk_combo_box_text_append_text(combo2, "bournemounth");
    gtk_combo_box_text_append_text(combo2, "Aston Villa");
    gtk_combo_box_text_append_text(combo2, "Fullham");
    gtk_combo_box_text_append_text(combo2, "Brighton");
    gtk_combo_box_text_append_text(combo2, "Tottenhem");
    gtk_combo_box_text_append_text(combo2, "Liverpool");
    gtk_combo_box_text_append_text(combo2, "Brentford");
    gtk_combo_box_text_append_text(combo2, "Newcastle United");
    gtk_combo_box_text_append_text(combo2, "Westham United");
    gtk_combo_box_text_append_text(combo2, "Crystal Palace");
    gtk_combo_box_text_append_text(combo2, "Everton");
    gtk_combo_box_text_append_text(combo2, "Leicester City");
    gtk_combo_box_text_append_text(combo2, "Wolverhempton");
    gtk_combo_box_text_append_text(combo2, "Ipswhich");
    gtk_combo_box_text_append_text(combo2, "Southampton");
    
}
