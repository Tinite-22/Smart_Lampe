// =====================================================================
// PROJET : Commande de relais par capteur infrarouge (IR)
// FONCTION : Un passage devant le capteur change l'état du relais (ON/OFF)
// =====================================================================

// --- Définition des broches (Pinout) ---
// Utilisation de 'const' pour figer les numéros de broches (gain de mémoire)
const int irSensor = 8;    // Le capteur envoie 0 (LOW) quand il détecte un obstacle
const int relayPin = 7;    // La broche qui pilote le module relais

// --- Variables de gestion d'état ---
int sensorState = 0;       // Stocke la lecture actuelle du capteur (HIGH ou LOW)
int lastSensorState = 1;   // Stocke l'état précédent (initialisé à 1 car le capteur est HIGH au repos)
bool relayActive = false;  // Variable "mémoire" : est-ce que notre système considère le relais comme actif ?

void setup() {
  // Configuration des sens de circulation du courant
  pinMode(irSensor, INPUT);      // Le capteur envoie des informations à l'Arduino
  pinMode(relayPin, OUTPUT);     // L'Arduino envoie des ordres au relais
  
  // INITIALISATION DU RELAIS :
  // La plupart des modules relais sont "Active Low" (s'activent au signal LOW).
  // On met donc la broche à HIGH au démarrage pour s'assurer que le relais est BIEN ÉTEINT.
  digitalWrite(relayPin, HIGH); 
  
  Serial.begin(9600);            // Ouvre le moniteur série pour le débogage
  Serial.println("Systeme pret !");
}

void loop() {
  // 1. Lire ce qui se passe devant le capteur
  sensorState = digitalRead(irSensor);

  // 2. ANALYSE DU CHANGEMENT D'ÉTAT 
  // On cherche le moment précis où l'objet arrive devant le capteur.
  // C'est-à-dire quand on passe de "Rien" (HIGH) à "Obstacle" (LOW).
  if (sensorState == LOW && lastSensorState == HIGH) { // Si le capteur passe à LOW(Obstacle détecté) alors qu'il etait à High (Au repos)
    
    // On inverse l'état de notre variable mémoire (si c'était faux, ça devient vrai)
    relayActive = !relayActive; 

    // 3. ACTION SUR LE RELAIS
    // Si relayActive est vrai (true), on envoie LOW pour fermer le contact du relais (Ce dernier agit ici comme un interrupteur).
    // Si relayActive est faux (false), on envoie HIGH pour ouvrir le contact.
    if (relayActive == true) {
      digitalWrite(relayPin, LOW);  // Allume le relais
      Serial.println("Relais : ACTIVE (ON)");
    } else {
      digitalWrite(relayPin, HIGH); // Éteint le relais
      Serial.println("Relais : DESACTIVE (OFF)");
    }

    // 4. ANTI-REBOND (Debounce)
    // Empêche le relais de "cliqueter" follement si le passage de l'objet est hésitant.
    // On attend 500ms avant d'autoriser une nouvelle détection.
    delay(500); 
  }

  // 5. MÉMORISATION
  // On enregistre l'état actuel pour comparer au prochain tour de boucle.
  lastSensorState = sensorState;
}