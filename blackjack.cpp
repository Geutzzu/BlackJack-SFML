#include <iostream>
#include <cstring>
#include <utility>
#include <vector>
#include <random>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <direct.h>
#include <functional>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

/// Update and Render class

class UpdateAndRender { /// clasa de baza pentru update si render

public:
    virtual void update() = 0;
    virtual void render() = 0;
};




/// enum a fost folosit pentru a face codul mai usor de citit si de inteles iar functiile de conversie sunt folosite pentru a afisa mai usor informatiile

enum Suit {
    HEARTS = 1, DIAMONDS, CLUBS, SPADES /// vor fi indexate de la 1 la 4
};

enum Rank {
    ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING /// vor fi indexate de la 1 la 13
};

enum ChipType {
    WHITE = 1, RED, BLUE, GREEN, BLACK, PURPLE, YELLOW /// 1, 5, 10, 25, 100, 500, 1000 - de tinut minte
};

int value(ChipType chipValue) /// functie care returneaza valoarea unui chip
{
    switch (chipValue) {
    case WHITE:
        return 1;
    case RED:
        return 5;
    case BLUE:
        return 10;
    case GREEN:
        return 25;
    case BLACK:
        return 100;
    case PURPLE:
        return 500;
    case YELLOW:
        return 1000;
    default:
        throw runtime_error("Invalid chip value");
    }
}


string suitToString(Suit suit) {
    switch (suit) {
    case HEARTS:
        return "HEARTS";
    case DIAMONDS:
        return "DIAMONDS";
    case CLUBS:
        return "CLUBS";
    case SPADES:
        return "SPADES";
    default:
        throw runtime_error("Invalid suit");
    }
}

string rankToString(Rank rank) {
    switch (rank) {
    case ACE:
        return "ACE";
    case TWO:
        return "TWO";
    case THREE:
        return "THREE";
    case FOUR:
        return "FOUR";
    case FIVE:
        return "FIVE";
    case SIX:
        return "SIX";
    case SEVEN:
        return "SEVEN";
    case EIGHT:
        return "EIGHT";
    case NINE:
        return "NINE";
    case TEN:
        return "TEN";
    case JACK:
        return "JACK";
    case QUEEN:
        return "QUEEN";
    case KING:
        return "KING";
    default:
        throw runtime_error("Invalid rank");
    }
}

string chipValueToString(ChipType chipValue) {
    switch (chipValue) {
    case WHITE:
        return "WHITE";
    case RED:
        return "RED";
    case BLUE:
        return "BLUE";
    case GREEN:
        return "GREEN";
    case BLACK:
        return "BLACK";
    case PURPLE:
        return "PURPLE";
    case YELLOW:
        return "YELLOW";
    default:
        throw runtime_error("Invalid chip value");
    }
}

Suit stringToSuit(const string& suit) {
    if (suit == "HEARTS")
        return HEARTS;
    if (suit == "DIAMONDS")
        return DIAMONDS;
    if (suit == "CLUBS")
        return CLUBS;
    if (suit == "SPADES")
        return SPADES;
    throw runtime_error("Invalid suit");
}

Rank stringToRank(const string& rank) {
    if (rank == "ACE")
        return ACE;
    if (rank == "TWO")
        return TWO;
    if (rank == "THREE")
        return THREE;
    if (rank == "FOUR")
        return FOUR;
    if (rank == "FIVE")
        return FIVE;
    if (rank == "SIX")
        return SIX;
    if (rank == "SEVEN")
        return SEVEN;
    if (rank == "EIGHT")
        return EIGHT;
    if (rank == "NINE")
        return NINE;
    if (rank == "TEN")
        return TEN;
    if (rank == "JACK")
        return JACK;
    if (rank == "QUEEN")
        return QUEEN;
    if (rank == "KING")
        return KING;
    throw runtime_error("Invalid rank");
}

ChipType stringToChipType(const string& chipValue) {
    if (chipValue == "WHITE")
        return WHITE;
    if (chipValue == "RED")
        return RED;
    if (chipValue == "BLUE")
        return BLUE;
    if (chipValue == "GREEN")
        return GREEN;
    if (chipValue == "BLACK")
        return BLACK;
    if (chipValue == "PURPLE")
        return PURPLE;
    if (chipValue == "YELLOW")
        return YELLOW;
    throw runtime_error("Invalid chip value");
}


vector<int> fromFloatToChips(float bet) { /// transformam un float in chipsuri de cele 7 valori
    vector<int> chips(7, 0); // Initialize a vector with 7 zeros
    int remainingBet = bet;
    for (int i = 6; i >= 0; --i) {
        while (remainingBet >= value(static_cast<ChipType>(i + 1))) {
            chips[i]++;
            remainingBet -= value(static_cast<ChipType>(i + 1));
        }
    }
    return chips;
}


class TextureManager { /// clasa pentru a incarca texturi
private:
    unordered_map<string, Texture> textures;
    unordered_map<string, Font> fonts;

public:
    void loadTexture(const string& name, const string& filename); /// functie care incarca textura

    Texture& getTexture(const string& name) { /// functie care returneaza textura
        return textures.at(name);
    }

    Font& getFont(const string& name) { /// functie care returneaza fontul
    		return fonts.at(name);
    }

    void loadCardTextures(); /// functie care incarca texturile cartilor

    void loadFont(const string& name, const string& filename); /// functie care incarca fontul


    void loadFonts(); /// functie care incarca fonturile


};

void TextureManager::loadTexture(const string& name, const string& filename) { /// functie care incarca textura
    Texture texture;
    if (!texture.loadFromFile(filename)) {
        cout << "Failed to load texture: " + filename << endl;
    }
    else cout << "Loaded texture: " + filename << endl;
    textures[name] = texture;
}

void TextureManager::loadCardTextures() { /// functie care incarca texturile cartilor
    string suits[] = { "hearts", "diamonds", "clubs", "spades" };
    string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king", "ace" };

    for (const auto& suit : suits) {
        for (const auto& rank : ranks) {
            string path = "Resources/Cards/" + rank + "_of_" + suit + ".png";
            Texture texture;
            if (!texture.loadFromFile(path)) {
                cout << "Failed to load texture: " + path << endl;
            }
            else cout << "Loaded texture: " + path << endl;
            textures[rank + "_of_" + suit] = texture;
        }
    }
    string path = "Resources/Cards/back.png";
    Texture texture;
    if (!texture.loadFromFile(path)) {
        cout << "Failed to load texture: " + path << endl;
    }
    textures["back"] = texture;
}

void TextureManager::loadFont(const string& name, const string& filename) { /// functie care incarca fontul
	Font font;
    if (!font.loadFromFile(filename)) {
		cout << "Failed to load font: " + filename << endl;
	}
	else cout << "Loaded font: " + filename << endl;
	fonts[name] = font;
}

void TextureManager::loadFonts() {

    loadFont("roboto", "Resources/Roboto-Black.ttf");
}

class Button : public RectangleShape { /// este responsabil si pentru chipsuri si pentru butoane
protected:
    Color normalColor;
    Color hoverColor;
    function<void()> onClick;
    Text buttonText;

public:
    Button() = default;

    Button(float x, float y, float width, float height, Color color, Color hoverColor, function<void()> onClickFunction, const Font& font, const string& text);

    void checkEvents(RenderWindow& window, Event event);

    void setOnClick(function<void()> onClickFunction) {
        onClick = onClickFunction;
    }

    void draw(RenderWindow& window) {
        window.draw(static_cast<RectangleShape&>(*this));
        window.draw(buttonText);
    }

    function<void()> getOnClickFunction() const { return onClick; }

};

Button::Button(float x, float y, float width, float height, Color color, Color hoverColor, function<void()> onClickFunction, const Font& font, const string& text)
    : RectangleShape(Vector2f(width, height)), normalColor(color), hoverColor(hoverColor), onClick(onClickFunction) {
    this->setPosition(x, y);
    this->setFillColor(normalColor);

    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(Color::Black);
    buttonText.setPosition(x, y);

    FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    buttonText.setPosition(Vector2f(x + width / 2.0f, y + height / 2.0f));
}

void Button::checkEvents(RenderWindow& window, Event event) {
    Vector2i mousePos = Mouse::getPosition(window);
    if (this->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        this->setFillColor(hoverColor);
        if (event.type == Event::MouseButtonReleased) {
            onClick();
        }
    }
    else {
        this->setFillColor(normalColor);
    }
}

class ChipButton : public Button { /// clasa pentru butoanele de chipsuri
private:
    ChipType chipValue;
    static TextureManager textureManager;
    Texture texture;
    Sprite sprite;

public:

    static void textureManagerLoadChipTextures(); /// functie care incarca texturile chipsurilor

    ChipButton(); /// constructor fara parametrii

    ChipButton(float x, float y, float width, float height, Color color, Color hoverColor, function<void()> onClickFunction, const Font& font, const string& text, ChipType chipValue);

    ChipButton(const ChipButton& a); /// copy constructor

    ChipButton& operator=(const ChipButton& a); /// supraincarcare operator =

    void draw(RenderWindow& window); /// functie de desenare

    ChipType getChipValue() const { return this->chipValue; } /// getter pentru chipValue
    void setChipValue(ChipType chipValue) { this->chipValue = chipValue; } /// setter pentru chipValue


    ~ChipButton() {
        /// nu avem nimic de sters
    }


};


void ChipButton::draw(RenderWindow& window) { /// functie de desenare
    this->buttonText.setOrigin(0, 0);
    this->sprite.setOrigin(0, 0);
    this->sprite.setPosition(this->getPosition());
    window.draw(sprite);

    FloatRect spriteBounds = sprite.getGlobalBounds();
    FloatRect textBounds = buttonText.getLocalBounds();
    float textX = spriteBounds.left + (spriteBounds.width / 2.0f) - (textBounds.width / 2.0f);
    float textY = spriteBounds.top + (spriteBounds.height / 2.0f) - (textBounds.height / 2.0f);
    buttonText.setPosition(textX, textY - 5);
    this->buttonText.setOrigin(0, 0);
    this->buttonText.setScale(0.85, 0.85);

    window.draw(buttonText);
}

void ChipButton::textureManagerLoadChipTextures() { /// functie care incarca texturile chipsurilor
    textureManager.loadTexture("WHITE_chip", "Resources/Chips/white_chip.png");
    textureManager.loadTexture("RED_chip", "Resources/Chips/red_chip.png");
    textureManager.loadTexture("BLUE_chip", "Resources/Chips/blue_chip.png");
    textureManager.loadTexture("GREEN_chip", "Resources/Chips/green_chip.png");
    textureManager.loadTexture("BLACK_chip", "Resources/Chips/black_chip.png");
    textureManager.loadTexture("PURPLE_chip", "Resources/Chips/purple_chip.png");
    textureManager.loadTexture("YELLOW_chip", "Resources/Chips/yellow_chip.png");
}

ChipButton::ChipButton() : chipValue(WHITE) { /// constructor fara parametrii
    this->texture = textureManager.getTexture(chipValueToString(WHITE) + "_chip");
    this->sprite.setTexture(texture);
    sprite.setScale(0.85, 0.85);
    this->buttonText.setFillColor(Color::White);

}

ChipButton::ChipButton(float x, float y, float width, float height, Color color, Color hoverColor, function<void()> onClickFunction, const Font& font, const string& text, ChipType chipValue)
    : Button(x, y, width, height, color, hoverColor, onClickFunction, font, text), chipValue(chipValue) {
    this->texture = textureManager.getTexture(chipValueToString(chipValue) + "_chip");
    cout << chipValueToString(chipValue) + "_chip" << endl;
    this->sprite.setTexture(texture);
    sprite.setScale(0.85, 0.85);
    this->buttonText.setFillColor(Color::White);
}

ChipButton::ChipButton(const ChipButton& a) : Button(a), chipValue(a.chipValue) { /// copy constructor
    this->texture = textureManager.getTexture(chipValueToString(chipValue) + "_chip");
    cout << chipValueToString(chipValue) + "_chip" << endl;
    this->sprite.setTexture(texture);
    sprite.setScale(0.85, 0.85);
    this->buttonText.setFillColor(Color::White);
}

ChipButton& ChipButton::operator=(const ChipButton& a) { /// supraincarcare operator =
    if (this != &a) {
        Button::operator=(a);
        this->chipValue = a.chipValue;
        this->texture = textureManager.getTexture(chipValueToString(chipValue) + "_chip");
        cout << chipValueToString(chipValue) + "_chip" << endl;
        this->sprite.setTexture(texture);
        sprite.setScale(0.85, 0.85);
        this->buttonText.setFillColor(Color::White);
    }
    return *this;
}



class Hand; /// declarare forward pentru a putea folosi clasa Hand in clasa Card

class Card { /// cartile de joc
private:
    Suit suit;
    Rank rank;
    int value; //// deoarece AS-ul poate fi 1 sau 11, prin conventie vom folosi 1 si tinem minte ca putem avea si 11
    bool isFaceUp; /// pentru a ascunde cartea dealerul

    Sprite sprite; /// pentru a afisa cartea
    Texture* texture; /// pentru a incarca textura
    Vector2f position; /// pozitia cartii
    float scale; /// scara cartii

    static TextureManager textureManager; /// pentru a incarca texturi

public:

    static void textureManagerLoadCardTextures() { /// functie care incarca texturile cartilor
        textureManager.loadCardTextures();
    }

    void initializeTexture(); /// functie care initializeaza textura cartii

    void setCardValue(); /// functie care seteaza valoarea cartii 

    Card(); /// constructor fara parametrii

    Card(Suit suit, Rank rank); /// primul constructor cu parametrii

    Card(Suit suit, Rank rank, bool isFaceUp); /// al doilea constructor cu parametrii

    Card(const Card& a); ///  copy constructor

    Card& operator=(const Card& a); /// supraincarcare operator =

    Hand operator+(const Card& c); /// adauga o carte cu alta carte si formeaza o mana - pentru punctul 9)

    Hand operator+(const Hand& h); /// adauga o carte cu o mana si formeaza o mana - pentru punctul 9)

    Card& operator++(); /// supraincarcare operator ++ (prefix)

    Card operator++(int); ///     supraincarcare operator ++ (postfix)

    Card operator[](int index); /// supraincarcare operator [] (incementeaza de index ori)

    ///int operator+(Card c); /// nu pot avea asta daca vreau sa adun 2 carti pentru a face un hand

    int operator-(Card c); /// supraincarcare operator -

    explicit operator string(); /// supraincarcare operator de cast explicit la string

    bool operator==(Card c); /// supraincarcare operator ==

    bool operator!=(Card c); /// supraincarcare operator !=

    bool operator>(Card c); ///  supraincarcare operator >

    bool operator<(Card c); /// supraincarcare operator <



    void render(RenderWindow& renderWindow); /// functie de render

    void hideCard(); /// functie care ascunde cartea
    void revealCard(); /// functie care arata cartea

    friend istream& operator>>(istream& in, Card& c); /// citire

    friend ostream& operator<<(ostream& out, const Card& c); /// afisare

    void setSuit(Suit suit) { this->suit = suit; } /// setter pentru suit
    Suit getSuit() { return this->suit; } /// getter pentru suit
    void setRank(Rank rank) { this->rank = rank; } /// setter pentru rank
    Rank getRank() { return this->rank; } /// getter pentru rank
    int getValue() const { return this->value; } /// getter pentru value
    bool getIsFaceUp() const { return this->isFaceUp; } /// getter pentru isFaceUp
    void setIsFaceUp(bool isFaceUp) { this->isFaceUp = isFaceUp; } /// setter pentru isFaceUp
    Texture* getTexture() { return this->texture; } /// getter pentru texture
    Sprite getSprite() { return this->sprite; } /// getter pentru sprite
    float setScale(float scale) { this->scale = scale; 
        this->sprite.setScale(this->scale, this->scale); /// trebuie initializat pentru render 
    } /// setter pentru scale
    float getScale() { return this->scale; } /// getter pentru scale
    void setPosition(Vector2f position) { this->position = position; } /// setter pentru position
    Vector2f getPosition() { return this->position; } /// getter pentru position

    ~Card() /// destructor
    {
        /// nu avem nimic de sters
    }
};

void Card::initializeTexture() {
    string lowercaseSuit = suitToString(this->suit);
    string lowercaseRank = rankToString(this->rank);
    transform(lowercaseSuit.begin(), lowercaseSuit.end(), lowercaseSuit.begin(),
        [](unsigned char c) { return tolower(c); });
    if (this->rank >= TWO && this->rank <= TEN)
    {
        lowercaseRank = to_string(static_cast<int>(this->rank));
    }
    else {
        transform(lowercaseRank.begin(), lowercaseRank.end(), lowercaseRank.begin(),
            [](unsigned char c) { return tolower(c); });
    }
    string path = lowercaseRank + "_of_" + lowercaseSuit;

    this->texture = &this->textureManager.getTexture(path);
    this->sprite.setTexture(*this->texture);
    this->sprite.setScale(this->scale, this->scale);

}



void Card::render(RenderWindow& renderWindow) {
    /// functie de render
    this->sprite.setPosition(this->position); // Set the position before drawing the sprite

    if (this->isFaceUp)
        renderWindow.draw(this->sprite);
    else {
        this->texture = &this->textureManager.getTexture("back");
        this->sprite.setTexture(*this->texture);
        this->sprite.setScale(this->scale + 0.2, this->scale + 0.2);
        renderWindow.draw(this->sprite);
    }
}

void Card::hideCard() {
    this->texture = &this->textureManager.getTexture("back");
    this->sprite.setTexture(*this->texture);
    this->sprite.setScale(this->scale, this->scale);
}

void Card::revealCard() {
    this->isFaceUp = true;
    this->initializeTexture();
}


void Card::setCardValue() {
    if (this->rank == ACE)
        this->value = 11; /// prin conventie vom folosi 11 si tinem minte ca putem avea si 1
    else if (this->rank >= TWO && this->rank <= TEN)
        this->value = this->rank;
    else
        this->value = 10;
}

Card::Card() /// contructor fara parametrii (pune niste valori arbitrare)
{
    this->suit = HEARTS;
    this->rank = TWO;
    this->value = 2;
    this->isFaceUp = true;
    this->texture = &this->textureManager.getTexture("2_of_hearts");
    this->scale = 0.3;
}

Card::Card(Suit suit, Rank rank) /// primul constructor cu parametrii
{
    this->suit = suit;
    this->rank = rank;
    if (rank == ACE)
        this->value = 11; /// prin conventie vom folosi 11 si tinem minte ca putem avea si 1
    else if (rank >= TWO && rank <= TEN)
        this->value = rank;
    else
        this->value = 10;
    this->isFaceUp = true;


    this->scale = 0.3;
    this->initializeTexture();

}

Card::Card(Suit suit, Rank rank, bool isFaceUp) /// al doilea constructor cu parametrii
{
    this->suit = suit;
    this->rank = rank;
    if (rank == ACE)
        this->value = 11; /// prin conventie vom folosi 11 si tinem minte ca putem avea si 1
    else if (rank >= TWO && rank <= TEN)
        this->value = rank;
    else
        this->value = 10;
    this->isFaceUp = isFaceUp;

    this->scale = 0.3;

    if(!isFaceUp)
		this->texture = &this->textureManager.getTexture("back");
	else
		this->initializeTexture();


}

Card::Card(const Card& a) /// copy constructor
{
    this->suit = a.suit;
    this->rank = a.rank;
    this->value = a.value;
    this->isFaceUp = a.isFaceUp;
    this->scale = a.scale;
    this->texture = a.texture;
    this->sprite.setTexture(*this->texture);
    this->sprite.setScale(this->scale, this->scale);

}

Card& Card::operator=(const Card& a) /// supraincarcare operator =
{
    if (this != &a) {
        this->suit = a.suit;
        this->rank = a.rank;
        this->value = a.value;
        this->isFaceUp = a.isFaceUp;
        this->scale = a.scale;
        this->texture = a.texture;
        this->sprite.setTexture(*this->texture);
        this->sprite.setScale(this->scale, this->scale);
    }
    return *this;
}



Card& Card::operator++() /// supraincarcare operator ++ (prefix)
{
    if (this->rank == KING)
        this->rank = ACE;
    else this->rank = static_cast<Rank>(this->rank + 1);

    if (this->rank == ACE)
        this->value = 11;
    else if (this->rank >= TWO && this->rank <= TEN)
        this->value = this->rank;
    else
        this->value = 10;

    return *this;
}

Card Card::operator++(int) /// supraincarcare operator ++ (postfix)
{
    Card aux(*this);

    ++(*this);

    return aux;
}

Card Card::operator[](int index) /// supraincarcare operator [] (incementeaza de index ori)
{
    if (index == 0)
        return *this;
    else {
        for (int i = 0; i < index; i++)
            ++(*this);
        return *this;
    }
}

/*int Card::operator+(Card c) /// supraincarcare operator + (valoarea adaugata a doua carti) - nu pot avea asta daca vreau sa adun 2 carti pentru a face un hand
{
    return this->value+c.getValue();
}*/


int Card::operator-(Card c) /// supraincarcare operator -
{
    return this->value - c.getValue();
}

Card::operator string() /// supraincarcare operator de cast explicit la string
{
    return rankToString(this->rank) + " of " + suitToString(this->suit);
}

bool Card::operator==(Card c) /// supraincarcare operator ==
{
    return this->rank == c.getRank() && this->suit == c.getSuit();
}

bool Card::operator!=(Card c) /// supraincarcare operator !=
{
    return this->rank != c.getRank() || this->suit != c.getSuit();
}

bool Card::operator>(Card c) /// supraincarcare operator >
{
    return this->value > c.getValue();
}

bool Card::operator<(Card c) /// supraincarcare operator <
{
    return this->value < c.getValue();
}

istream& operator>>(istream& in, Card& c) /// citim stringuri si le convertim la tipurile de date corespunzatoare
{
    string suit, rank;
    cout << "Input suit and rank: " << endl;
    in >> suit >> rank;
    c.suit = stringToSuit(suit);
    c.rank = stringToRank(rank);
    c.setCardValue();
    return in;
}

ostream& operator<<(ostream& out, const Card& c) /// afisam stringuri convertite din tipurile de date corespunzatoare (denumire tip Suit of Rank)
{
    if (c.getIsFaceUp())
        out << rankToString(c.rank) << " of " << suitToString(c.suit) << endl;
    else out << "----------------" << endl;
    return out;
}


class GameDeck {
private:
    vector<Card> cards; /// vector de carti
    int decksCount; /// numarul de pachete de carti

public:
    void shuffle();
    Card dealCard();

    GameDeck(); /// constructor fara parametrii
    GameDeck(int decksCount); /// constructor cu parametrii relevanti
    GameDeck(int decksCount, bool shuffle); /// constructor cu parametrii relevanti
    GameDeck(const vector<Card>& cards, int decksCount); /// constructor cu parametrii relevanti

    GameDeck& operator=(const GameDeck& a); /// supraincarcare operator =
    Card operator[](int index); /// supraincarcare operator []
    GameDeck operator--(); /// supraincarcare operator --
    GameDeck operator--(int); /// supraincarcare operator --
    GameDeck operator+(Card c); /// supraincarcare operator +
    GameDeck operator-(Card c); /// supraincarcare operator -

    explicit operator int() const; /// supraincarcare operator de cast explicit la int
    bool operator==(const GameDeck& g); /// supraincarcare operator ==
    bool operator<(GameDeck g); /// supraincarcare operator <
    bool operator>(GameDeck g); /// supraincarcare operator >

    friend istream& operator>>(istream& in, GameDeck& g); /// citire
    friend ostream& operator<<(ostream& out, const GameDeck& g); /// afisare

    int getDecksCount() const { return this->decksCount; } //// getter pentru decksCount
    int getCardsLeft() const { return this->cards.size(); } /// getter pentru cardsLeft
    int getCardsDealt() const { return 52 * this->decksCount - this->cards.size(); } /// getter pentru cardsDealt
    const vector<Card>& getCards() const { return this->cards; } /// getter pentru cards

    ~GameDeck() {
        /// nu avem nimic de sters
    }
};


void GameDeck::shuffle() { /// functie de shuffle
    random_device rd;
    mt19937 g(rd());
    ::shuffle(cards.begin(), cards.end(), g);
}

Card GameDeck::dealCard() {
    if (!cards.empty()) {
        Card cardDealt = cards.back();
        cards.pop_back();
        return cardDealt;
    }
    ///throw runtime_error("No cards left");
    cout << "No cards left" << endl;
}

GameDeck::GameDeck() {
    this->decksCount = 1;
    this->cards.resize(52);

    int cardIndex = 0;
    for (int s = HEARTS; s <= SPADES; s++) {
        for (int r = ACE; r <= KING; r++) {
            this->cards[cardIndex] = Card(static_cast<Suit>(s), static_cast<Rank>(r)); /// adaugam cartile in pachet - trebuie facut cast
            cardIndex++;
        }
    }
}

GameDeck::GameDeck(int decksCount) {
    this->decksCount = decksCount;
    this->cards.resize(52 * decksCount);

    int cardIndex = 0;
    for (int d = 0; d < decksCount; d++) {
        for (int s = HEARTS; s <= SPADES; s++) { /// adaugam cartile in pachet - trebuie facut cast
            for (int r = ACE; r <= KING; r++) { /// adaugam cartile in pachet - trebuie facut cast
                this->cards[cardIndex] = Card(static_cast<Suit>(s), static_cast<Rank>(r)); /// adaugam cartile in pachet - trebuie facut cast
                cardIndex++;
            }
        }
    }
}

GameDeck::GameDeck(int decksCount, bool shuffle) {
    this->decksCount = decksCount;
    this->cards.resize(52 * decksCount);

    int cardIndex = 0;
    for (int d = 0; d < decksCount; d++) {
        for (int s = HEARTS; s <= SPADES; s++) {
            for (int r = ACE; r <= KING; r++) {
                this->cards[cardIndex] = Card(static_cast<Suit>(s), static_cast<Rank>(r)); /// adaugam cartile in pachet - trebuie facut cast
                cardIndex++;
            }
        }
    }

    if (shuffle) {
        this->shuffle();
    }
}

GameDeck::GameDeck(const vector<Card>& cards, int decksCount) {
    this->cards = cards;
    this->decksCount = decksCount;
}

/*GameDeck::GameDeck(const GameDeck &a) { /// copy constructorul deja definit este lafel
    this->cards = a.cards;
    this->decksCount = a.decksCount;

}*/

GameDeck& GameDeck::operator=(const GameDeck& a) {
    if (this != &a) {
        this->cards = a.cards;
        this->decksCount = a.decksCount;
    }
    return *this;
}

Card GameDeck::operator[](int index) {
    if (index >= 0 && index < 52 * this->decksCount)
        return this->cards[index];
    ///throw runtime_error("Invalid index");
    cout << "Invalid index" << endl;
}



istream& operator>>(istream& in, GameDeck& g) {
    cout << "Input number of decks: " << endl;
    in >> g.decksCount;
    g.cards.resize(52 * g.decksCount);


    int cardIndex = 0;
    for (int d = 0; d < g.decksCount; d++) {
        for (int s = HEARTS; s <= SPADES; s++) {
            for (int r = ACE; r <= KING; r++) {
                g.cards[cardIndex] = Card(static_cast<Suit>(s), static_cast<Rank>(r));
                cardIndex++;
            }
        }
    }
    return in;
}

ostream& operator<<(ostream& out, const GameDeck& g) {
    out << "Number of decks: " << endl;
    out << g.getDecksCount() << endl;

    out << "Cards left: " << endl;
    out << g.getCardsLeft() << endl;

    out << "Cards dealt: " << endl;
    out << g.getCardsDealt() << endl;

    out << "Cards: " << endl;
    out << endl;
    for (int i = 0; i < g.getCardsLeft(); i++)
        out << g.getCards()[i];

    return out;
}

class Hand {
private:
    vector<Card> cardsInHand; /// vector de carti
    int handValue[2]; /// valoarea mainii (poate fi 1 sau 11 pentru AS)
    bool isBusted; /// daca valoarea mainii este peste 21
    bool isBlackjack; /// daca valoarea mainii este 21 din prima mana
    bool splitable; /// daca poti face split
    bool isDoubledDown; /// daca ai dublat
    bool isFinished; /// daca ai terminat

    Font font;
    Text handText;
    Vector2f position;

    static TextureManager textureManager; /// pentru a incarca texturi

public:
    void calculateHandValue(); /// calculeaza valoarea mainii
    bool canSplit(); /// daca poti face split
    void initializeText(); /// initializeaza textul pentru valoarea mainii
    void updateText(); /// update la textul pentru valoarea mainii
    void render(RenderWindow& renderWindow); /// functie de render
    void renderText(RenderWindow& renderWindow); /// functie de render pentru text
    void hideText(); /// functie care ascunde textul
    bool containsAce(); /// daca contine un AS
        
    static void textureManagerLoadFont(); /// functie care incarca fontul


    Hand(); /// constructor fara parametrii
    Hand(vector<Card> cardsInHand); /// constructor cu parametrii relevanti
    Hand(const Hand& a); /// copy constructor
    Hand& operator=(const Hand& a); /// supraincarcare operator =
    Card operator[](int index) const; /// supraincarcare operator []
    ///Hand operator--(); /// supraincarcare operator --
    ///Hand operator--(int); /// supraincarcare operator --
    Hand operator+(const Card& c); /// adauga o carte in mana
    Hand operator+(const Hand& h); /// adauga o mana la alta
    Hand operator-(const Card& c); /// scoate o carte din mana
    ///explicit operator string() const; /// supraincarcare operator de cast explicit la string
    ///bool operator==(const Hand &h); /// supraincarcare operator ==
    ///bool operator>(const Hand &h); /// supraincarcare operator >
    ///bool operator<(const Hand &h); /// supraincarcare operator <
    friend istream& operator>>(istream& in, Hand& h); /// citire
    friend ostream& operator<<(ostream& out, const Hand& h); /// afisare
    int getHandValue(int index) const { return this->handValue[index]; } /// getter pentru handValue
    bool getIsBusted() const { return this->isBusted; } /// getter pentru isBusted
    bool getIsBlackjack() const { return this->isBlackjack; } /// getter pentru isBlackjack
    const vector<Card>& getCardsInHand() const { return this->cardsInHand; } /// getter pentru cardsInHand
    void setCardsInHand(vector<Card> cardsInHand) { this->cardsInHand = move(cardsInHand); } /// setter pentru cardsInHand
    void setIsBusted(bool isBusted) { this->isBusted = isBusted; } /// setter pentru isBusted
    void setIsBlackjack(bool isBlackjack) { this->isBlackjack = isBlackjack; } /// setter pentru isBlackjack
    int getCardsCount() const { return this->cardsInHand.size(); } /// getter pentru cardsInHandCount
    bool getIsSplitable() const { return this->splitable; } /// getter pentru splitable
    bool getIsDoubledDown() const { return this->isDoubledDown; } /// getter pentru isDoubledDown
    void setIsDoubledDown(bool isDoubledDown) { this->isDoubledDown = isDoubledDown; } /// setter pentru isDoubledDown
    void setSplitable(bool splitable) { this->splitable = splitable; } /// setter pentru splitable
    void setFinished(bool isFinished) { this->isFinished = isFinished; } /// setter pentru isFinished
    bool getIsFinished() const { return this->isFinished; } /// getter pentru isFinished 
    void setPosition(Vector2f position) { this->position = position; } /// setter pentru position
    Vector2f getPosition() { return this->position; } /// getter pentru position
    

    ~Hand() {
        /// nu avem nimic de sters
    }
};

Hand Card::operator+(const Card& c) { /// adauga o carte cu alta carte si formeaza o mana
    vector<Card> newCards = { *this, c }; /// vector de carti
    Hand newHand(newCards); /// mana noua
    newHand.calculateHandValue(); /// calculeaza valoarea mainii
    return newHand; /// returneaza mana
}

Hand Card::operator+(const Hand& h) { /// adauga o carte cu o mana si formeaza o mana
    vector<Card> newCards = h.getCardsInHand(); /// vector de carti
    newCards.push_back(*this); /// adauga o carte
    Hand newHand(newCards); /// mana noua
    newHand.calculateHandValue(); /// calculeaza valoarea mainii
    return newHand; /// returneaza mana
}

void Hand::textureManagerLoadFont() { /// functie care incarca fontul
    textureManager.loadFonts();
}


bool Hand::containsAce() { /// daca contine un AS
    for (Card card : this->cardsInHand) {
		if (card.getRank() == ACE)
			return true;
	}
	return false;
}

bool Hand::canSplit() { /// daca poti face split
    return this->cardsInHand.size() == 2 && this->cardsInHand[0].getRank() == this->cardsInHand[1].getRank();
}

void Hand::initializeText() {
    this->font = textureManager.getFont("roboto");
    this->handText.setFont(this->font);
    this->handText.setCharacterSize(24);
    this->handText.setFillColor(Color::White);
    this->handText.setPosition(this->position);
}

void Hand::hideText() {
	this->handText.setString("");
}

void Hand::updateText() {

    if (this->isBusted)
        this->handText.setString("BUSTED");
    else if (this->isBlackjack)
        this->handText.setString("BLACKJACK");
    else if (this->handValue[0] == this->handValue[1])
        this->handText.setString(to_string(this->handValue[0]));
    else this->handText.setString(to_string(this->handValue[0]) + " / " + to_string(this->handValue[1]));

}

void Hand::calculateHandValue() { /// calculeaza valoarea mainii
    int sum1 = 0;
    int sum2 = 0;
    for (Card card : this->cardsInHand) {
        if (card.getRank() == ACE) {
            sum1 += 1;
            sum2 += 11;
        }
        else {
            sum1 += card.getValue();
            sum2 += card.getValue();
        }
    }
    this->handValue[0] = sum1;
    this->handValue[1] = sum2;
    this->isBusted = sum1 > 21;
    this->isBlackjack = (sum2 == 21 || sum1 == 21) && this->cardsInHand.size() == 2; /// daca valoarea mainii este 21 din prima mana
    this->splitable = canSplit();
    if (this->isBusted || this->isBlackjack) /// daca ai terminat
        this->isFinished = true;
    this->updateText();
}

void Hand::render(RenderWindow& renderWindow) {  /// functie de render
    for (int i = 0; i < this->cardsInHand.size(); i++) {
        this->cardsInHand[i].setPosition(this->position + Vector2f(100 * i, 0));
        this->cardsInHand[i].render(renderWindow); /// render la fiecare carte , position + Vector2f(100 * i, 0)
    }
    this->renderText(renderWindow); /// render la text
}


void Hand::renderText(RenderWindow& renderWindow) { /// functie de render pentru text
    this->handText.setPosition(this->position + Vector2f(100 * this->cardsInHand.size() + 60, 0));
    if(this->cardsInHand[0].getIsFaceUp())
        renderWindow.draw(this->handText);
    else renderWindow.draw(Text());
}


Hand::Hand() : isBusted(false), isBlackjack(false) { /// constructor fara parametrii
    this->handValue[0] = 0;
    this->handValue[1] = 0;
    this->splitable = false;
    this->isDoubledDown = false;
    this->isFinished = false;
    this->position = Vector2f(0, 0);
    this->initializeText();
}

Hand::Hand(vector<Card> cardsInHand) : cardsInHand(move(cardsInHand)) { /// constructor cu parametrii relevanti
    this->initializeText();
    this->calculateHandValue();
    this->isDoubledDown = false;
    this->isFinished = false;
}

Hand::Hand(const Hand& a) : cardsInHand(a.cardsInHand), isBusted(a.isBusted), isBlackjack(a.isBlackjack) { /// Copy constructor
    handValue[0] = a.handValue[0];
    handValue[1] = a.handValue[1];
    this->splitable = a.splitable;
    this->isDoubledDown = a.isDoubledDown;
    this->isFinished = a.isFinished;
    this->position = a.position;

    this->initializeText();
    
}

Hand& Hand::operator=(const Hand& a) { /// supraincarcare operator =
    if (this != &a) {
        this->cardsInHand = a.cardsInHand;
        this->handValue[0] = a.handValue[0];
        this->handValue[1] = a.handValue[1];
        this->isBusted = a.isBusted;
        this->isBlackjack = a.isBlackjack;
        this->splitable = a.splitable;
        this->isDoubledDown = a.isDoubledDown;
        this->isFinished = a.isFinished;
        this->position = a.position;

        this->initializeText();
    }
    return *this;
}

Card Hand::operator[](int index) const { /// supraincarcare operator []
    if (index >= 0 && index < cardsInHand.size())
        return cardsInHand[index];
    throw runtime_error("Invalid index");
}


Hand Hand::operator+(const Card& c) { /// adauga o carte in mana
    vector<Card> newCards = cardsInHand;
    newCards.push_back(c);
    Hand newHand(newCards);
    newHand.calculateHandValue();
    newHand.isDoubledDown = this->isDoubledDown;
    newHand.initializeText();
    return newHand;
}

Hand Hand::operator+(const Hand& h) { /// adauga o mana la alta
    vector<Card> newCards = this->cardsInHand;
    newCards.insert(newCards.end(), h.cardsInHand.begin(), h.cardsInHand.end());
    Hand newHand(newCards);
    newHand.calculateHandValue();
    newHand.isDoubledDown = this->isDoubledDown || h.isDoubledDown;
    newHand.initializeText();
    return newHand;
}

Hand Hand::operator-(const Card& c) { /// scoate o carte din mana
    vector<Card> newCards = cardsInHand;
    newCards.erase(remove(newCards.begin(), newCards.end(), c), newCards.end());
    return { newCards };
}


istream& operator>>(istream& in, Hand& h) {
    int cardsInHandCount;
    cout << "Input number of cards in hand: " << endl;
    in >> cardsInHandCount;

    h.cardsInHand.clear();
    h.cardsInHand.resize(cardsInHandCount);
    for (int i = 0; i < cardsInHandCount; i++) {
        cout << "Input card " << i + 1 << ": " << endl;
        Card card;
        in >> card;
        h.cardsInHand[i] = card;
    }
    h.calculateHandValue();
    return in;
}

ostream& operator<<(ostream& out, const Hand& h) {
    out << "Number of cards in hand: " << endl;
    out << h.getCardsCount() << endl;

    out << "Hand value: " << endl;
    out << h.getHandValue(0) << " or " << h.getHandValue(1) << endl;

    out << "Is busted: " << endl;
    out << h.getIsBusted() << endl;

    out << "Is blackjack: " << endl;
    out << h.getIsBlackjack() << endl;


    out << "Cards in hand: " << endl;
    for (int i = 0; i < h.getCardsCount(); i++)
        out << h.getCardsInHand()[i];
    cout << endl;

    return out;
}

class Participant { /// clasa de baza pentru dealer si player
protected:
    string name;
    int age;
    int chips[7]; /// vector de chips-uri de diferite valori (WHITE, RED, BLUE, GREEN, BLACK, PURPLE, YELLOW)
    float balance; /// soldul participantului
    float winnings; ///  (cati bani a castigat fara a lua in considerare pierderile)
    float losses; ///  (cati bani a pierdut fara a lua in considerare castigurile)
    float positionX;
    float positionY;

public:

    Participant(); /// constructor fara parametrii
    Participant(string name, int age, int chips[7], float balance, float losses, float winnings, float positionX, float positionY); /// constructor cu parametrii relevanti
    Participant(const Participant& a); /// copy constructor
    Participant& operator=(const Participant& a); /// supraincarcare operator =
    ///friend istream& operator>>(istream& in, Participant& p); /// citire
    ///friend ostream& operator<<(ostream& out, const Participant& p); /// afisare

    /// metode virtuale pure
    virtual void initializeHand(GameDeck& gameDeck) = 0; /// va fi diferita implementarea primei maini pentru dealer si player
    virtual void clearHand() = 0; /// va fi diferita implementarea pentru dealer si player (playerul poate avea mai multe handuri)
    virtual void renderHands(RenderWindow& renderWindow) = 0; /// va fi diferita implementarea pentru dealer si player (playerul poate avea mai multe handuri)

    /// alte metode
    ///virtual void calculateBalance(); /// calculeaza soldul

    /// afisare si citire in consola pentru testare - prin supraincarcarea operatorului << si >>
    virtual istream& citire(istream& in);
    virtual ostream& afisare(ostream& out) const;

    friend istream& operator>>(istream& in, Participant& p);
    friend ostream& operator<<(ostream& out, const Participant& p);

    /// functii de getteri si setteri
    string getName() const { return this->name; } /// getter pentru name
    void setName(string name) { this->name = move(name); } /// setter pentru name
    int getAge() const { return this->age; } /// getter pentru age
    void setAge(int age) { this->age = age; } /// setter pentru age
    float getBalance() const { return this->balance; } /// getter pentru balance
    void setBalance(float balance) { this->balance = balance; } /// setter pentru balance
    int getChips(ChipType chipType) const { return this->chips[chipType]; } /// getter pentru chips
    void setChips(ChipType chipType, int value) { this->chips[chipType] = value; } /// setter pentru chips
    void setPositionX(float positionX) { this->positionX = positionX; } /// setter pentru positionX
    void setPositionY(float positionY) { this->positionY = positionY; } /// setter pentru positionY
    float getPositionX() const { return this->positionX; } /// getter pentru positionX
    float getPositionY() const { return this->positionY; } /// getter pentru positionY

    virtual ~Participant() {
        /// nu avem nimic de sters
    }
};


Participant::Participant() : name("Persoana"), age(18), balance(0), losses(0), winnings(0), positionX(0), positionY(0) { /// constructor fara parametrii
    for (int i = 0; i < 7; i++)
        chips[i] = 0; /// initializam chips-urile cu 0 - nu e folosit momentan
}

Participant::Participant(string name, int age, int chips[7], float balance, float losses, float winnings, float positionX, float positionY) : name(move(name)), age(age), balance(balance), losses(losses), winnings(winnings), positionX(positionX), positionY(positionY) { /// constructor cu parametrii relevanti
    for (int i = 0; i < 7; i++)
        this->chips[i] = chips[i]; /// initializam chips-urile cu valorile date
}

Participant::Participant(const Participant& a) : name(a.name), age(a.age), balance(a.balance), winnings(a.winnings), losses(a.losses), positionX(a.positionX), positionY(a.positionY) { /// copy constructor
    for (int i = 0; i < 7; i++)
        this->chips[i] = a.chips[i]; /// copiem chips-urile
}

Participant& Participant::operator=(const Participant& a) { /// supraincarcare operator =
    if (this != &a) {
        this->name = a.name;
        this->age = a.age;
        this->balance = a.balance;
        this->winnings = a.winnings;
        this->losses = a.losses;
        this->positionX = a.positionX;
        this->positionY = a.positionY;
        for (int i = 0; i < 7; i++)
            this->chips[i] = a.chips[i];
    }
    return *this;
}

istream& Participant::citire(istream& in) { /// citire
    cout << "Input name: " << endl;
    in >> this->name;
    cout << "Input age: " << endl;
    in >> this->age;
    cout << "Input balance: " << endl;
    in >> this->balance;
    cout << "Input winnings: " << endl;
    in >> this->winnings;
    cout << "Input losses: " << endl;
    in >> this->losses;
    cout << "Input positionX: " << endl;
    in >> this->positionX;
    cout << "Input positionY: " << endl;
    in >> this->positionY;
    cout << "Input chips: " << endl;
    for (int i = 0; i < 7; i++)
        in >> this->chips[i];
    return in;
}

ostream& Participant::afisare(ostream& out) const { /// afisare
    out << "Name: " << this->name << endl;
    out << "Age: " << this->age << endl;
    out << "Balance: " << this->balance << endl;
    out << "Winnings: " << this->winnings << endl;
    out << "Losses: " << this->losses << endl;
    out << "PositionX: " << this->positionX << endl;
    out << "PositionY: " << this->positionY << endl;
    out << "Chips: " << endl;
    for (int i = 0; i < 7; i++)
        out << this->chips[i] << " ";
    out << endl;
    return out;
}

istream& operator>>(istream& in, Participant& p) { /// citire
    return p.citire(in);
}

ostream& operator<<(ostream& out, const Participant& p) { /// afisare
    return p.afisare(out);
}

class Player : virtual public Participant { /// clasa pentru player
protected:
    vector<Hand> hands; /// vector de maini
    float bet; /// pariu
    float initialBet; /// pariu initial

    ///float insuranceBet; /// pariu pentru insurance ! DOAR JUMATE DIN INITIAL BET NU E NEV DE VARIABILA ASTA

public:

    Player(); /// constructor fara parametrii
    Player(string name, int age, int chips[7], float balance, float bet, float initialBet, float positionX, float positionY); /// constructor cu parametrii relevanti

    Player(const Player& a); /// copy constructor
    Player& operator=(const Player& a); /// supraincarcare operator =

    /// functii virtuale pure
    void initializeHand(GameDeck& gameDeck) override; /// va fi diferita implementarea primei maini pentru dealer si player
    void clearHand() override; /// va fi diferita implementarea pentru dealer si player (playerul poate avea mai multe handuri) 

    /// afisare citire
    istream& citire(istream& in) override;
    ostream& afisare(ostream& out) const override;
    friend istream& operator>>(istream& in, Player& p);
    friend ostream& operator<<(ostream& out, const Player& p);


    /// alte metode
    void doubleDown(int index, GameDeck& gameDeck); /// dubleaza handul index
    void insurance(int index); /// face insurance
    void split(int index, GameDeck& gameDeck); /// face split 

    /// metode pentru joc
    void hit(int index, GameDeck& gameDeck); /// ia o carte
    void stand(int index); /// termina cu mana
    void initializeBet(float initialBet); /// initializeaza betul
    void clearBet(); /// sterge betul
    void addToBet(float value); /// adauga la bet

    /// metode de render
    void renderHands(RenderWindow& renderWindow) override; /// render pentru maini

    /// functii de getteri si setteri

    int getBet() const { return this->bet; } /// getter pentru bet
    const vector<Hand>& getHands() const { return this->hands; } /// getter pentru hands
    void setHands(vector<Hand> hands) { this->hands = move(hands); } /// setter pentru hands
    void setHand(int index, Hand hand) { this->hands[index] = move(hand); } /// setter pentru o mana
    void setBet(float bet) { this->bet = bet; } /// setter pentru bet
    void setInitialBet(float initialBet) { this->initialBet = initialBet; } /// setter pentru initialBet
    float getInitialBet() const { return this->initialBet; } /// getter pentru initialBet


};

Player::Player() : Participant(), bet(0), initialBet(0) { /// constructor without parameters
    this->hands.push_back(Hand());
    /// Button(float x, float y, float width, float height, Color color, Color hoverColor, function<void()> onClickFunction, const Font& font, const string& text)

}

Player::Player(string name, int age, int chips[7], float balance, float bet, float initialBet, float positionX, float positionY) : Participant(name, age, chips, balance, losses, winnings, positionX, positionY), bet(bet), initialBet(initialBet) { /// constructor with relevant parameters
    hands.push_back(Hand());
}

Player::Player(const Player& a) : Participant(a), hands(a.hands) { /// copy constructor
    this->bet = a.bet;
    this->initialBet = a.initialBet;
}


Player& Player::operator=(const Player& a) { /// overload assignment operator
    if (this != &a) {
        Participant::operator=(a);
        this->bet = a.bet;
        this->initialBet = a.initialBet;
        this->hands = a.hands;
    }
    return *this;
}

/// Initializing the hand
void Player::initializeHand(GameDeck& gameDeck) { /// vom avea o mana initializata cu 2 carti
    hands.clear();
    hands.push_back(Hand());
    hands[0] = hands[0] + gameDeck.dealCard();
    hands[0] = hands[0] + gameDeck.dealCard();
    hands[0].calculateHandValue();
}

/// Clearing the hand
void Player::clearHand() { /// stergem mana
    hands.clear();
}

void Player::stand(int index) { /// termina cu o mana
    if (index < hands.size() && index >= 0) {
        hands[index].calculateHandValue();
        hands[index].setFinished(true);
    }
    else {
        ///throw runtime_error("Invalid index");
        cout << "Invalid index" << endl;
    }
}



void Player::hit(int index, GameDeck& gameDeck) { /// ia o carte
    if (index < this->hands.size() && index >= 0) {
        if (this->hands[index].getIsFinished())
            return;
        this->hands[index] = this->hands[index] + gameDeck.dealCard();
        hands[index].calculateHandValue();
    }
    else {
        ///throw runtime_error("Invalid index");
        cout << "Invalid index" << endl;
    }
}

void Player::renderHands(RenderWindow& renderWindow) { /// render pentru maini
    for (int i = 0; i < hands.size(); i++) {
        hands[i].setPosition(Vector2f(0, 100 * i) + Vector2f(this->positionX, this->positionY));  /// setam pozitia mainii
        hands[i].render(renderWindow);
    }
}

void Player::initializeBet(float initialBet) { /// initializeaza betul
    this->initialBet = initialBet;
    this->bet = initialBet;
}

void Player::clearBet() { /// sterge betul
    this->bet = 0;
    this->initialBet = 0;
}


void Player::addToBet(float value) { /// adauga la bet
    if (value > 0) {
        this->initialBet += value;
    }
    else {
        ///throw runtime_error("Invalid value");
        cout << "Invalid value" << endl;
    }
}

/// Double down
/// Jucatorul dubleaza betul si primeste o singura carte
/// Dupa ce primeste cartea, nu mai poate trage
/// Jucaotrul nu poate dubla daca a tras mai mult de o carte
/// Can double down on a split hand
void Player::doubleDown(int index, GameDeck& gameDeck) { /// da double down la o mana si termina cu ea
    if (index < hands.size() && index >= 0) {
        if (this->hands[index].getCardsCount() == 2 && !this->hands[index].getIsFinished()) {
            this->hands[index] = this->hands[index] + gameDeck.dealCard();
            this->bet = this->bet + this->initialBet;
            this->balance = this->balance - this->initialBet;
            this->hands[index].calculateHandValue();
            this->hands[index].setIsDoubledDown(true);
            this->hands[index].setFinished(true);
        }
        else {
            cout << "Cannot double down" << endl;
        }
    }
    else {
        cout << "Invalid index" << endl;
    }
}

void Player::insurance(int index) { /// makes insurance (nu e tocmai corect) - cel mai simplu pentru beturi total corecte ar fi sa renuntam la chipuri
    if (index < hands.size() && index >= 0) {
        if (this->hands[index].getCardsCount() == 2 && this->balance >= this->initialBet) {
            int insuranceBet = this->initialBet / 2; /// jumatate din bet
            this->bet = this->bet + insuranceBet; /// adaugam un insurance bet la bet (pentru fiecare bet mai adaugam dar asta se va face din clasa game)
            this->balance = this->balance - insuranceBet; /// scadem din balance
        }
        else {
            cout << "Cannot make insurance" << endl;
        }
    }
    else {
        cout << "Invalid index" << endl;
    }
}

void Player::split(int Index, GameDeck& gameDeck) { /// face split la o mana
    if (Index < 0 || Index >= this->hands.size()) {
        cout << "Invalid index" << endl;
        return;
    }

    Hand& handToSplit = this->hands[Index];

    if (!handToSplit.canSplit() || hands.size() > 4) {
        cout << "Cannot split" << endl;
        return;
    }

    vector<Card> cardsInHand = handToSplit.getCardsInHand();
    vector<Card> newHand1Cards = { cardsInHand[0] };
    vector<Card> newHand2Cards = { cardsInHand[1] };

    Hand newHand1(newHand1Cards);
    Hand newHand2(newHand2Cards);

    this->hands[Index] = newHand1;
    this->hands.push_back(newHand2);

    this->hands[hands.size() - 1].calculateHandValue();
    this->hands[Index].calculateHandValue();


    this->setBet(this->getBet() + this->initialBet);
    this->balance = this->balance - this->initialBet;
}

istream& Player::citire(istream& in) { /// citire
    Participant::citire(in);
    cout << "Input bet: " << endl;
    in >> this->bet;
    cout << "Input initial bet: " << endl;
    in >> this->initialBet;
    cout << "Input hands count: " << endl;
    int handsCount;
    in >> handsCount;
    hands.clear();
    hands.resize(handsCount);
    for (int i = 0; i < handsCount; i++) {
        cout << "Input hand " << i + 1 << ": " << endl;
        in >> hands[i];
    }
    return in;
}

ostream& Player::afisare(ostream& out) const { /// afisare
    Participant::afisare(out);
    out << "Bet: " << this->bet << endl;
    out << "Initial bet: " << this->initialBet << endl;
    out << "Hands count: " << this->hands.size() << endl;
    for (int i = 0; i < this->hands.size(); i++) {
        out << "Hand " << i + 1 << ": " << endl;
        out << this->hands[i];
    }
    return out;
}

istream& operator>>(istream& in, Player& p) { /// citire
    return p.citire(in);
}

ostream& operator<<(ostream& out, const Player& p) { /// afisare
    return p.afisare(out);
}



class Dealer : virtual public Participant { /// clasa pentru dealer
protected:
    Hand hand; /// mana dealerului

public:
    Dealer(); /// constructor fara parametrii
    Dealer(string name, int age, int chips[7], float balance, float losses, float winnings, float positionX, float positionY); /// constructor cu parametrii relevanti
    Dealer(const Dealer& a); /// copy constructor
    Dealer& operator=(const Dealer& a); /// supraincarcare operator =

    /// functii virtuale pure
    void initializeHand(GameDeck& gameDeck) override; /// va fi diferita implementarea primei maini pentru dealer si player
    void clearHand() override; /// va fi diferita implementarea pentru dealer si player (playerul poate avea mai multe handuri)

    /// functii render
    void renderHands(RenderWindow& renderWindow) override{ /// render pentru mana
    		hand.setPosition(Vector2f(this->positionX, this->positionY));
    		hand.render(renderWindow);
    }

    /// afisare citire
    istream& citire(istream& in) override;
    ostream& afisare(ostream& out) const override;
    friend istream& operator>>(istream& in, Dealer& d);
    friend ostream& operator<<(ostream& out, const Dealer& d);

    /// alte metode
    void dealerPlay(GameDeck& gameDeck); /// dealerul joaca (ia carti pana cand valoarea mainii este peste 17)

    /// functii de getteri si setteri
    const Hand& getHand() const { return this->hand; } /// getter pentru hand
    void setHand(Hand hand) { this->hand = move(hand); } /// setter pentru hand

};


Dealer::Dealer() : Participant() { /// constructor fara parametrii
    hand = Hand();
}

Dealer::Dealer(string name, int age, int chips[7], float balance, float losses, float winnings, float positionX, float positionY) : Participant(name, age, chips, balance, losses, winnings, positionX, positionY) { /// constructor cu parametrii relevanti
    hand = Hand();
}

Dealer::Dealer(const Dealer& a) : Participant(a), hand(a.hand) { /// copy constructor
}

Dealer& Dealer::operator=(const Dealer& a) { /// overload assignment operator
    if (this != &a) {
        Participant::operator=(a);
        this->hand = a.hand;
    }
    return *this;
}

/// Initializing the hand
void Dealer::initializeHand(GameDeck& gameDeck) { /// vom avea o mana initializata cu 2 carti
    this->hand = Hand();
    this->hand = hand + gameDeck.dealCard();
    Card card = hand[0];
    card.setIsFaceUp(false); /// a trb sa fac asa ca operatoru plus nu schimba valoarea
    this->hand = card + gameDeck.dealCard();
    this->hand.calculateHandValue();
}

/// Clearing the hand
void Dealer::clearHand() { /// stergem mana
    this->hand = Hand();
}

/// Dealer play
void Dealer::dealerPlay(GameDeck& gameDeck) { /// dealerul joaca (ia carti pana cand valoarea mainii este peste 17)

    if (hand.getIsBlackjack())
    {
        Card card = hand[0];
        card.revealCard();
        this->hand = card + hand[1];
        this->hand.setFinished(true);
    }

    else if (!hand.getIsFinished())
    {
        Card card = hand[0];
        card.revealCard();
        this->hand = card + hand[1];
        while (this->hand.getHandValue(0) < 17) {
            if (this->hand.getHandValue(1) >= 17 && hand.getHandValue(1) <= 21)
                break;
            this->hand = hand + gameDeck.dealCard();
            this->hand.calculateHandValue();
        }
        this->hand.setFinished(true);
    }
    this->hand.initializeText();

} ///  ar trebui sa avem dealerul intr-un stadiu corect dupa functia asta cu isBlackjack si isBusted

istream& Dealer::citire(istream& in) { /// citire
    Participant::citire(in);
    cout << "Input hand: " << endl;
    in >> this->hand;
    return in;
}

ostream& Dealer::afisare(ostream& out) const { /// afisare
    Participant::afisare(out);
    out << "Hand: " << endl;
    out << this->hand;
    return out;
}

istream& operator>>(istream& in, Dealer& d) { /// citire
    return d.citire(in);
}

ostream& operator<<(ostream& out, const Dealer& d) { /// afisare
    return d.afisare(out);
}


class DealerPlayer : public Player, public Dealer { /// clasa pentru dealerul care este si player, in teorie poate juca un joc singur

private:
    /// nu avem nevoie de variabile noi

public:
    DealerPlayer(); /// constructor fara parametrii
    DealerPlayer(string name, int age, int chips[7], float balance, float bet, float initialBet, float positionX, float positionY); /// constructor cu parametrii relevanti
    DealerPlayer(const DealerPlayer& a); /// copy constructor
    DealerPlayer& operator=(const DealerPlayer& a); /// supraincarcare operator =

    /// functii virtuale pure
    void initializeHand(GameDeck& gameDeck) override;/// va fi diferita implementarea primei maini pentru dealer si player
    void clearHand() override; /// va fi diferita implementarea pentru dealer si player (playerul poate avea mai multe handuri)
    void renderHands(RenderWindow& renderWindow) override; /// va fi diferita implementarea pentru dealer si player (playerul poate avea mai multe handuri)

    /// afisare citire
    istream& citire(istream& in) override; /// citire
    ostream& afisare(ostream& out) const override; /// afisare
    friend istream& operator>>(istream& in, DealerPlayer& dp);  /// citire
    friend ostream& operator<<(ostream& out, const DealerPlayer& dp); /// afisare

    /// functii de getteri si setteri
    const Hand& getHand() const { return this->hand; } /// getter pentru hand
    void setHand(Hand hand) { this->hand = move(hand); } /// setter pentru hand
    const vector<Hand>& getHands() const { return this->hands; } /// getter pentru hands
    void setHands(vector<Hand> hands) { this->hands = move(hands); } /// setter pentru hands


};

void DealerPlayer::renderHands(RenderWindow& renderWindow) { /// render pentru maini
    for (int i = 0; i < hands.size(); i++) {
		hands[i].setPosition(Vector2f(0, 100 * i) + Vector2f(this->positionX, this->positionY));  /// setam pozitia mainii
		hands[i].render(renderWindow);
	}
	hand.setPosition(Vector2f(this->positionX, this->positionY + 100 * hands.size()));
	hand.render(renderWindow);
}

void DealerPlayer::initializeHand(GameDeck& gameDeck) { /// vom avea o mana initializata cu 2 carti
    Player::initializeHand(gameDeck); /// initializeaza handurile - aici e un vector
    Dealer::initializeHand(gameDeck); /// initializeaza mana dealerului - aici e doar una
}

void DealerPlayer::clearHand() { /// stergem mana
    Player::clearHand(); /// sterge handurile - aici e un vector
    Dealer::clearHand(); /// sterge mana dealerului - aici e doar una
}

DealerPlayer::DealerPlayer() : Player(), Dealer(), Participant() { /// constructor fara parametrii
}

DealerPlayer::DealerPlayer(string name, int age, int chips[7], float balance, float bet, float initialBet, float positionX, float positionY) /// constructor cu parametrii relevanti
    : Player(name, age, chips, balance, bet, initialBet, positionX, positionY),
    Dealer(name, age, chips, balance, bet, initialBet, positionX, positionY) {

}

DealerPlayer::DealerPlayer(const DealerPlayer& a) : Player(a), Dealer(a) { /// copy constructor
}

DealerPlayer& DealerPlayer::operator=(const DealerPlayer& a) { /// overload assignment operator
    if (this != &a) {
        Player::operator=(a);
        Dealer::operator=(a);
    }
    return *this;
}


istream& DealerPlayer::citire(istream& in) { /// citire
    Player::citire(in);
    cout << "Input dealer hand: " << endl;
    in >> hand;
    return in;
}

ostream& DealerPlayer::afisare(ostream& out) const { /// afisare
    Player::afisare(out);
    cout << "Dealer hand: " << endl;
    out << hand;
    return out;
}

istream& operator>>(istream& in, DealerPlayer& dp) { /// citire
    return dp.citire(in);
}

ostream& operator<<(ostream& out, const DealerPlayer& dp) { /// afisare
    return dp.afisare(out);
}


class Game { /// va folosi un singur jucator si un dealer - de facut o alta classa pentru mai multi jucatori
private:
    GameDeck gameDeck;
    vector<Participant*> participants;

    /// Gameplay buttons
    Button hitButton;
    Button standButton;
    Button doubleDownButton;
    Button splitButton;
    Button insuranceButton;
    Button restartButton;

    /// Chip buttons
    ChipButton whiteChipButton;
    ChipButton redChipButton;
    ChipButton blueChipButton;
    ChipButton greenChipButton;
    ChipButton blackChipButton;
    ChipButton purpleChipButton;
    ChipButton yellowChipButton;

    /// Text
    Font font;
    Text gameState;
    Text balanceText;
    Text betText;
    Text placeBetText;

    /// Textures
    static TextureManager textureManager;


public:

    static void textureManagerLoadFont(); /// incarca fontul


    Game(); /// constructor fara parametrii
    Game(int decksCount, bool shuffle); /// constructor cu parametrii relevanti
    Game(int decksCount, bool shuffle, const vector<Participant*>& participants); /// constructor cu parametrii relevanti

    Game(const Game& a); /// copy constructor
    Game& operator=(const Game& a); /// supraincarcare operator =


    /// initializing buttons
    void initializeButtons(); /// initializeaza butoanele

    void initializeGame(); /// initializeaza jocul
    //void clearGame(); /// sterge jocul
    void render(RenderWindow& renderWindow, bool playerHasBetted); /// functie de render
    void update(bool playerHasBetted); /// functie de update
    void runtime(RenderWindow& renderWindow); /// functie de runtime
    void updateBalance(); /// update la balance
    void updateBet(); /// update la bet
    void updateGameState(bool playerHasBetted); /// update la game state
    void updateButtonFunctions(); /// update la functiile butoanelor
    void restartGame(); /// restart la joc
    void renderBettingChips(RenderWindow& renderWindow); /// render la chips-uri



    /// setere si getere
    const GameDeck& getGameDeck() const { return this->gameDeck; } /// getter pentru gameDeck
    void setGameDeck(const GameDeck& gameDeck) { this->gameDeck = gameDeck; } /// setter pentru gameDeck
    const vector<Participant*>& getParticipants() const { return this->participants; } /// getter pentru participants
    void setParticipants(const vector<Participant*>& newParticipants) {
        for (Participant* participant : this->participants) {
            delete participant;
        }
        this->participants.clear();
        for (Participant* participant : newParticipants) {
            this->participants.push_back(participant);
        }
    } /// setter pentru participants

    Button getHitButton() const { return this->hitButton; } /// getter pentru hitButton
    Button getStandButton() const { return this->standButton; } /// getter pentru standButton
    Button getDoubleDownButton() const { return this->doubleDownButton; } /// getter pentru doubleDownButton
    Button getSplitButton() const { return this->splitButton; } /// getter pentru splitButton
    Button getInsuranceButton() const { return this->insuranceButton; } /// getter pentru insuranceButton
    void setHitFunction(function<void()> onClickFunction) { this->hitButton.setOnClick(onClickFunction); } /// setter pentru hitButton
    void setStandFunction(function<void()> onClickFunction) { this->standButton.setOnClick(onClickFunction); } /// setter pentru standButton
    void setDoubleDownFunction(function<void()> onClickFunction) { this->doubleDownButton.setOnClick(onClickFunction); } /// setter pentru doubleDownButton
    void setSplitFunction(function<void()> onClickFunction) { this->splitButton.setOnClick(onClickFunction); } /// setter pentru splitButton
    void setInsuranceFunction(function<void()> onClickFunction) { this->insuranceButton.setOnClick(onClickFunction); } /// setter pentru insuranceButton
    void setGameState(const string& gameState) { this->gameState.setString(gameState); } /// setter pentru gameState
    void setBalanceText(const string& balanceText) { this->balanceText.setString(balanceText); } /// setter pentru balanceText
    void setBetText(const string& betText) { this->betText.setString(betText); } /// setter pentru betText
    void setPlaceBetText(const string& placeBetText) { this->placeBetText.setString(placeBetText); } /// setter pentru placeBetText


    ~Game() {
        for (Participant* participant : participants) {
            delete participant;
        }
    }

};


void Game::textureManagerLoadFont() { /// incarca fontul
    textureManager.loadFonts();
}

void Game::restartGame() {
    /// de dat clear la handuri si de initializat handurile



    this->gameState.setString("Players turn");

    this->gameDeck = GameDeck(2, true);


    for (Participant* participant : participants) {
        participant->clearHand();
        participant->initializeHand(gameDeck);
    }

    int bet = dynamic_cast<Player*>(participants[1])->getInitialBet();
    int initialBalance = dynamic_cast<Player*>(participants[1])->getBalance();
    dynamic_cast<Player*>(participants[1])->setBalance(initialBalance - bet);
    dynamic_cast<Player*>(participants[1])->setBet(bet);
    this->updateBalance();
    this->updateBet();


    this->hitButton.setOnClick([this]() {
        if (this->participants.size() > 1)
            dynamic_cast<Player*>(this->participants[1])->hit(0, this->gameDeck);
        });
    this->doubleDownButton.setOnClick([this]() {
        if (this->participants.size() > 1)
            dynamic_cast<Player*>(this->participants[1])->doubleDown(0, this->gameDeck);
        });
    this->standButton.setOnClick([this]() {
        if (this->participants.size() > 1)
            dynamic_cast<Player*>(this->participants[1])->stand(0);
        });
    this->splitButton.setOnClick([this]() {
        if (this->participants.size() > 1)
            dynamic_cast<Player*>(this->participants[1])->split(0, this->gameDeck);
        });
    this->insuranceButton.setOnClick([this]() {
        if (this->participants.size() > 1)
            dynamic_cast<Player*>(this->participants[1])->insurance(0);
        });

}


void Game::initializeButtons() { /// multe butoane - cu functiile lor

    this->hitButton = Button(76, 670, 150, 50, Color::Green, Color::Red, [this]() {
        if (this->participants.size() > 1 && dynamic_cast<Player*>(this->participants[1]))
            dynamic_cast<Player*>(this->participants[1])->hit(0, this->gameDeck);

        }, this->font, "Hit");
    this->doubleDownButton = Button(338, 670, 150, 50, Color::Green, Color::Red, [this]() {
        if (this->participants.size() > 1 && dynamic_cast<Player*>(this->participants[1]))
            dynamic_cast<Player*>(this->participants[1])->doubleDown(0, this->gameDeck);
        }, this->font, "Double Down");
    this->standButton = Button(588, 670, 150, 50, Color::Green, Color::Red, [this]() {
        if (this->participants.size() > 1 && dynamic_cast<Player*>(this->participants[1]))
            dynamic_cast<Player*>(this->participants[1])->stand(0);
        }, this->font, "Stand");
    this->splitButton = Button(844, 670, 150, 50, Color::Green, Color::Red, [this]() {
        if (this->participants.size() > 1 && dynamic_cast<Player*>(this->participants[1]))
            dynamic_cast<Player*>(this->participants[1])->split(0, this->gameDeck);
        }, this->font, "Split");
    this->insuranceButton = Button(1100, 670, 150, 50, Color::Green, Color::Red, [this]() {
        if (this->participants.size() > 1 && dynamic_cast<Player*>(this->participants[1]))
            dynamic_cast<Player*>(this->participants[1])->insurance(0);
        }, this->font, "Insurance");
    this->restartButton = Button(1100, 450, 150, 50, Color::Green, Color::Red, [this]() {
        this->restartGame();
        }, this->font, "Restart");


    this->whiteChipButton = ChipButton(900, 150, 50, 50, Color::White, Color::Red, [this]() {
        if (this->participants.size() > 1 && dynamic_cast<Player*>(this->participants[1]))
            dynamic_cast<Player*>(this->participants[1])->addToBet(1);
        int bet = dynamic_cast<Player*>(this->participants[1])->getInitialBet();
        dynamic_cast<Player*>(this->participants[1])->setBet(bet);
        dynamic_cast<Player*>(this->participants[1])->setBalance(dynamic_cast<Player*>(this->participants[1])->getBalance() - 1);
        }, this->font, "1", WHITE);
    this->redChipButton = ChipButton(900, 220, 50, 50, Color::White, Color::Red, [this]() {
        if (this->participants.size() > 1 && dynamic_cast<Player*>(this->participants[1]))
            dynamic_cast<Player*>(this->participants[1])->addToBet(5);
        int bet = dynamic_cast<Player*>(this->participants[1])->getInitialBet();
        dynamic_cast<Player*>(this->participants[1])->setBet(bet);
        dynamic_cast<Player*>(this->participants[1])->setBalance(dynamic_cast<Player*>(this->participants[1])->getBalance() - 5);
        }, this->font, "5", RED);
    this->blueChipButton = ChipButton(900, 290, 50, 50, Color::White, Color::Red, [this]() {
        if (this->participants.size() > 1 && dynamic_cast<Player*>(this->participants[1]))
            dynamic_cast<Player*>(this->participants[1])->addToBet(10);
        int bet = dynamic_cast<Player*>(this->participants[1])->getInitialBet();
        dynamic_cast<Player*>(this->participants[1])->setBet(bet);
        dynamic_cast<Player*>(this->participants[1])->setBalance(dynamic_cast<Player*>(this->participants[1])->getBalance() - 10);
        }, this->font, "10", BLUE);
    this->greenChipButton = ChipButton(900, 370, 50, 50, Color::White, Color::Red, [this]() {
        if (this->participants.size() > 1 && dynamic_cast<Player*>(this->participants[1]))
            dynamic_cast<Player*>(this->participants[1])->addToBet(25);
        int bet = dynamic_cast<Player*>(this->participants[1])->getInitialBet();
        dynamic_cast<Player*>(this->participants[1])->setBet(bet);
        dynamic_cast<Player*>(this->participants[1])->setBalance(dynamic_cast<Player*>(this->participants[1])->getBalance() - 25);
        }, this->font, "25", GREEN);
    this->blackChipButton = ChipButton(900, 440, 50, 50, Color::White, Color::Red, [this]() {
        if (this->participants.size() > 1 && dynamic_cast<Player*>(this->participants[1]))
            dynamic_cast<Player*>(this->participants[1])->addToBet(100);
        int bet = dynamic_cast<Player*>(this->participants[1])->getInitialBet();
        dynamic_cast<Player*>(this->participants[1])->setBet(bet);
        dynamic_cast<Player*>(this->participants[1])->setBalance(dynamic_cast<Player*>(this->participants[1])->getBalance() - 100);
        }, this->font, "100", BLACK);
    this->purpleChipButton = ChipButton(900, 510, 50, 50, Color::White, Color::Red, [this]() {
        if (this->participants.size() > 1 && dynamic_cast<Player*>(this->participants[1]))
            dynamic_cast<Player*>(this->participants[1])->addToBet(500);
        int bet = dynamic_cast<Player*>(this->participants[1])->getInitialBet();
        dynamic_cast<Player*>(this->participants[1])->setBet(bet);
        dynamic_cast<Player*>(this->participants[1])->setBalance(dynamic_cast<Player*>(this->participants[1])->getBalance() - 500);
        }, this->font, "500", PURPLE);
    this->yellowChipButton = ChipButton(900, 580, 50, 50, Color::White, Color::Red, [this]() {
        if (this->participants.size() > 1 && dynamic_cast<Player*>(this->participants[1]))
            dynamic_cast<Player*>(this->participants[1])->addToBet(1000);
        int bet = dynamic_cast<Player*>(this->participants[1])->getInitialBet();
        dynamic_cast<Player*>(this->participants[1])->setBet(bet);
        dynamic_cast<Player*>(this->participants[1])->setBalance(dynamic_cast<Player*>(this->participants[1])->getBalance() - 1000);
        }, this->font, "1000", YELLOW);
}


Game::Game() { /// constructor fara parametrii
    this->gameDeck = GameDeck();
    this->participants.push_back(new Dealer());
    this->font = textureManager.getFont("roboto");
    this->gameState.setFont(this->font);
    this->gameState.setCharacterSize(24);
    this->gameState.setFillColor(Color::White);
    this->gameState.setPosition(1050, 50);
    this->gameState.setString("Game state");
    this->balanceText.setFont(this->font);
    this->balanceText.setCharacterSize(24);
    this->balanceText.setFillColor(Color::White);
    this->balanceText.setPosition(1050, 100);
    this->balanceText.setString("Balance: 0");
    this->betText.setFont(this->font);
    this->betText.setCharacterSize(24);
    this->betText.setFillColor(Color::White);
    this->betText.setPosition(1050, 150);
    this->betText.setString("Bet: 0");
    /// Button(float x, float y, float width, float height, Color color, Color hoverColor, function<void()> onClickFunction, const Font& font, const string& text)
    this->hitButton = Button(0, 0, 150, 50, Color::Green, Color::Red, [this]() {}, this->font, "Hit");
    this->doubleDownButton = Button(0, 150, 100, 50, Color::Green, Color::Red, [this]() {}, this->font, "Double Down");
    this->standButton = Button(0, 0, 150, 50, Color::Green, Color::Red, [this]() {}, this->font, "Stand");
    this->splitButton = Button(0, 0, 150, 50, Color::Green, Color::Red, [this]() {}, this->font, "Split");
    this->insuranceButton = Button(0, 150, 100, 50, Color::Green, Color::Red, [this]() {}, this->font, "Insurance");
    this->restartButton = Button(0, 0, 150, 50, Color::Green, Color::Red, [this]() {
        this->restartGame();
        }, this->font, "Restart");
}

Game::Game(int decksCount, bool shuffle) : gameDeck(decksCount, shuffle) { /// constructor cu parametrii relevanti
    this->participants.push_back(new Dealer());
    for (int i = 0; i < 2; i++) {
        this->participants.push_back(new Player());
    }
    this->font = textureManager.getFont("roboto");
    this->gameState.setFont(this->font);
    this->gameState.setCharacterSize(24);
    this->gameState.setFillColor(Color::White);
    this->gameState.setPosition(1050, 50);
    this->gameState.setString("Game state");
    this->balanceText.setFont(this->font);
    this->balanceText.setCharacterSize(24);
    this->balanceText.setFillColor(Color::White);
    this->balanceText.setPosition(1050, 100);
    this->balanceText.setString("Balance: 0");
    this->betText.setFont(this->font);
    this->betText.setCharacterSize(24);
    this->betText.setFillColor(Color::White);
    this->betText.setPosition(1050, 150);
    this->betText.setString("Bet: 0");
    this->initializeButtons();

}

Game::Game(int decksCount, bool shuffle, const vector<Participant*>& participants)
    : gameDeck(decksCount, shuffle) {
    for (Participant* participant : participants) {
        if (dynamic_cast<Dealer*>(participant)) {
            this->participants.push_back(new Dealer(*dynamic_cast<Dealer*>(participant)));
        }
        else if (dynamic_cast<Player*>(participant)) {
            this->participants.push_back(new Player(*dynamic_cast<Player*>(participant)));
        }
    }
    this->font = textureManager.getFont("roboto");
    this->gameState.setFont(this->font);
    this->gameState.setCharacterSize(24);
    this->gameState.setFillColor(Color::White);
    this->gameState.setPosition(1050, 50);
    this->gameState.setString("Game state");
    this->balanceText.setFont(this->font);
    this->balanceText.setCharacterSize(24);
    this->balanceText.setFillColor(Color::White);
    this->balanceText.setPosition(1050, 100);
    this->balanceText.setString("Balance: 0");
    this->betText.setFont(this->font);
    this->betText.setCharacterSize(24);
    this->betText.setFillColor(Color::White);
    this->betText.setPosition(1050, 150);
    this->betText.setString("Bet: 0");
    this->initializeButtons();
}

Game::Game(const Game& a) : gameDeck(a.gameDeck) {
    // Copy the participants
    for (Participant* participant : participants) {
        delete participant;
    }
    this->participants.clear();


    for (Participant* participant : a.participants) {
        if (dynamic_cast<Dealer*>(participant)) { /// daca participantul este dealer
            this->participants.push_back(new Dealer(*dynamic_cast<Dealer*>(participant)));
        }
        else if (dynamic_cast<Player*>(participant)) {
            this->participants.push_back(new Player(*dynamic_cast<Player*>(participant)));
        }
    }
    this->font = a.font;
    this->gameState = a.gameState;
    this->balanceText = a.balanceText;
    this->betText = a.betText;
    this->hitButton = a.hitButton;
    this->doubleDownButton = a.doubleDownButton;
    this->standButton = a.standButton;
    this->splitButton = a.splitButton;
    this->insuranceButton = a.insuranceButton;
    this->restartButton = a.restartButton;
    this->whiteChipButton = a.whiteChipButton;
    this->redChipButton = a.redChipButton;
    this->blueChipButton = a.blueChipButton;
    this->greenChipButton = a.greenChipButton;
    this->blackChipButton = a.blackChipButton;
    this->purpleChipButton = a.purpleChipButton;
    this->yellowChipButton = a.yellowChipButton;
}

Game& Game::operator=(const Game& a) {
    if (this != &a) {
        // Delete the old participants
        for (Participant* participant : participants) {
            delete participant;
        }
        this->participants.clear();

        // Copy the game deck
        this->gameDeck = a.gameDeck;

        // Copy the participants
        for (Participant* participant : a.participants) {
            if (dynamic_cast<Dealer*>(participant)) {
                this->participants.push_back(new Dealer(*dynamic_cast<Dealer*>(participant)));
            }
            else if (dynamic_cast<Player*>(participant)) {
                this->participants.push_back(new Player(*dynamic_cast<Player*>(participant)));
            }
        }

        this->font = a.font;
        this->gameState = a.gameState;
        this->balanceText = a.balanceText;
        this->betText = a.betText;
        this->hitButton = a.hitButton;
        this->doubleDownButton = a.doubleDownButton;
        this->standButton = a.standButton;
        this->splitButton = a.splitButton;
        this->insuranceButton = a.insuranceButton;
        this->restartButton = a.restartButton;
        this->whiteChipButton = a.whiteChipButton;
        this->redChipButton = a.redChipButton;
        this->blueChipButton = a.blueChipButton;
        this->greenChipButton = a.greenChipButton;
        this->blackChipButton = a.blackChipButton;
        this->purpleChipButton = a.purpleChipButton;
        this->yellowChipButton = a.yellowChipButton;

    }
    return *this;
}


void Game::initializeGame() { /// initializeaza jocul
    

    for (Participant* participant : this->participants) { /// exemplu bun de polimorfism
        participant->initializeHand(gameDeck);
        if (dynamic_cast<Player*>(participant)) {
			Player* player = dynamic_cast<Player*>(participant);
            player->setPositionX(100);
            player->setPositionY(350);
		}
        else if (dynamic_cast<Dealer*>(participant)) {
            Dealer* dealer = dynamic_cast<Dealer*>(participant);
            dealer->setPositionX(100);
            dealer->setPositionY(20);
        }
    }
}


void Game::updateBalance() {
    /// update la balance
    for (Participant* participant : this->participants) {
        if (dynamic_cast<Player*>(participant)) {
            Player* player = dynamic_cast<Player*>(participant);
            this->balanceText.setString("Balance: " + to_string(player->getBalance()));
        }
    }
}

void Game::updateBet() {
    /// update la bet
    for (Participant* participant : this->participants) {
        if (dynamic_cast<Player*>(participant)) {
            Player* player = dynamic_cast<Player*>(participant);
            this->betText.setString("Bet: " + to_string(player->getBet()));
        }
    }
}

/// update la functiile de split, double down, hit, stand
void Game::updateButtonFunctions() {
    /// daca o mana este finished functiile trec la mana urmatoare
    /// daca toate mainile sunt finished se trece la dealer
    Player* player = dynamic_cast<Player*>(participants[1]);
    int numberOfHands = player->getHands().size();
    int lastFinishedHand = -1;
    for (int i = 0; i < numberOfHands; i++) {
        if (player->getHands()[i].getIsFinished()) {
            lastFinishedHand = i;
        }
    }
    this->hitButton.setOnClick([this, lastFinishedHand, player]() {
        player->hit(lastFinishedHand + 1, this->gameDeck);
        });

    this->doubleDownButton.setOnClick([this, lastFinishedHand, player]() {
        player->doubleDown(lastFinishedHand + 1, this->gameDeck);
        });

    this->standButton.setOnClick([this, lastFinishedHand, player]() {
        player->stand(lastFinishedHand + 1);
        });

    this->splitButton.setOnClick([this, lastFinishedHand, player]() {
        player->split(lastFinishedHand + 1, this->gameDeck);
        });

    this->insuranceButton.setOnClick([this, lastFinishedHand, player]() {
        player->insurance(lastFinishedHand + 1);
        });

}

void Game::updateGameState(bool playerHasBetted) {
    /// update la game state

    Player* player = dynamic_cast<Player*>(participants[1]);
    Dealer* dealer = dynamic_cast<Dealer*>(participants[0]);
    bool allPlayersFinished = true;
    for (Hand hand : player->getHands()) {
        if (!hand.getIsFinished()) {
            allPlayersFinished = false;
            break;
        }
    }

    if (this->gameState.getString() == "Game ended") {
        /// aici ramanem
    }
    else if (allPlayersFinished) {
        this->setGameState("Dealer played");
    }
    else if (!playerHasBetted) {
        this->setGameState("Place your bet");
    }
    else {
        this->setGameState("Players turn");
    }

}


void Game::renderBettingChips(RenderWindow& renderWindow) {
    /// render la chips-uri
    this->whiteChipButton.draw(renderWindow); /// de facut o functie de draw in clasa de baza
    this->redChipButton.draw(renderWindow); /// de facut o functie de draw in clasa de baza
    this->blueChipButton.draw(renderWindow); /// de facut o functie de draw in clasa de baza
    this->greenChipButton.draw(renderWindow); /// de facut o functie de draw in clasa de baza
    this->blackChipButton.draw(renderWindow); /// de facut o functie de draw in clasa de baza
    this->purpleChipButton.draw(renderWindow); /// de facut o functie de draw in clasa de baza
    this->yellowChipButton.draw(renderWindow); /// de facut o functie de draw in clasa de baza
}


void Game::update(bool playerHasBetted) {
    bool allPlayersFinished = false;

    this->updateBalance();
    this->updateBet();
    this->updateGameState(playerHasBetted);
    this->updateButtonFunctions();

    Player* player = dynamic_cast<Player*>(participants[1]);

    for (Hand hand : player->getHands()) {
        cout << "Player hand: " << hand << endl;
        if (!hand.getIsFinished()) {
            allPlayersFinished = false;
            break;
        }
        allPlayersFinished = true;
    }
    cout << allPlayersFinished << endl;
    if (allPlayersFinished && this->gameState.getString() != "Game ended") {
        Dealer* dealer = dynamic_cast<Dealer*>(participants[0]);
        dealer->dealerPlay(gameDeck);
        cout << "Dealer hand: " << dealer->getHand() << endl;

        for (Hand hand : player->getHands()) {
            int handValue = hand.getHandValue(0);
            if (hand.containsAce() && hand.getHandValue(1) <= 21) {
                handValue = hand.getHandValue(1);
            }

            if (hand.getIsBusted()) {
                cout << "Player busted" << endl;
                continue;
            }
            if (dealer->getHand().getHandValue(0) > 21) {
                cout << "Dealer busted" << endl;
                if (hand.getIsBlackjack()) {
                    cout << "Player wins with blackjack" << endl;
                    player->setBalance(player->getBalance() + 2.5 * player->getInitialBet());
                }
                else {
                    cout << "Player wins" << endl;
                    player->setBalance(player->getBalance() + 2 * player->getInitialBet());
                }
                continue;
            }
            if (dealer->getHand().getIsBlackjack() && !hand.getIsBlackjack()) {
                cout << "Dealer wins with blackjack" << endl;
                continue;
            }
            if (handValue > dealer->getHand().getHandValue(0)) {
                if (hand.getIsBlackjack()) {
                    cout << "Player wins with blackjack" << endl;
                    player->setBalance(player->getBalance() + 2.5 * player->getInitialBet());
                }
                else {
                    cout << "Player wins" << endl;
                    player->setBalance(player->getBalance() + 2 * player->getInitialBet());
                }
            }
            else if (handValue == dealer->getHand().getHandValue(0)) {
                if (hand.getIsBlackjack() && dealer->getHand().getIsBlackjack()) {
                    cout << "Push" << endl;
                    player->setBalance(player->getBalance() + player->getInitialBet());
                }
                else if (hand.getIsBlackjack()) {
                    cout << "Player wins with blackjack" << endl;
                    player->setBalance(player->getBalance() + 2.5 * player->getInitialBet());
                }
                else {
                    cout << "Push" << endl;
                    player->setBalance(player->getBalance() + player->getInitialBet());
                }
            }
            else {
                cout << "Dealer wins" << endl;
            }
        }
        this->updateBalance();
        this->updateBet();
        this->setGameState("Game ended");
    }
}


/// nu da render la tot doar functia asta momentan de refacut
void Game::render(RenderWindow& renderWindow, bool playerHasBetted) { /// functie de render
    if (!playerHasBetted) {
        Hand placeholderHand;
        Card card = Card();
        card.setIsFaceUp(false);
        placeholderHand = placeholderHand + card;
        placeholderHand = placeholderHand + card;


        placeholderHand.setPosition(Vector2f(100, 350));
        placeholderHand.render(renderWindow); ///  Vector2f(100, 350)
        placeholderHand.setPosition(Vector2f(100, 20));
        placeholderHand.render(renderWindow); /// Vector2f(100, 20)
    }

    else {
        for (Participant* participant : this->participants) {
            participant->renderHands(renderWindow);
            
        }
    }

    this->hitButton.draw(renderWindow);
    this->doubleDownButton.draw(renderWindow);
    this->standButton.draw(renderWindow);
    this->splitButton.draw(renderWindow);
    this->insuranceButton.draw(renderWindow);
    this->restartButton.draw(renderWindow);
    renderWindow.draw(this->gameState);
    renderWindow.draw(this->balanceText);
    renderWindow.draw(this->betText);

    if (!playerHasBetted) {
        this->renderBettingChips(renderWindow);
    }
}


void Game::runtime(RenderWindow& renderWindow) { /// functie de runtime - trebuie puse toate lucruril unde trebuie

    bool playerHasBetted = false;
    this->initializeGame();
    this->render(renderWindow, playerHasBetted);

    while (renderWindow.isOpen()) { /// cat timp fereastra este deschisa

        Event event;
        while (renderWindow.pollEvent(event)) { /// cat timp sunt evenimente
            if (event.type == Event::Closed) {
                renderWindow.close();
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) /// keyboard events
            {
                this->hitButton.getOnClickFunction()();  /// functie de apelare a functiei de onClick
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::D) /// keyboard events
            {
                this->doubleDownButton.getOnClickFunction()(); /// functie de apelare a functiei de onClick
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::S)
            {
                this->standButton.getOnClickFunction()(); /// functie de apelare a functiei de onClick
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::P)
            {
                this->splitButton.getOnClickFunction()(); /// functie de apelare a functiei de onClick
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::I)
            {
                this->insuranceButton.getOnClickFunction()();
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
            {
                this->restartButton.getOnClickFunction()();
            }
            else
                if (!playerHasBetted) {
                    this->whiteChipButton.checkEvents(renderWindow, event); /// de pus in functie de update
                    this->redChipButton.checkEvents(renderWindow, event);
                    this->blueChipButton.checkEvents(renderWindow, event);
                    this->greenChipButton.checkEvents(renderWindow, event);
                    this->blackChipButton.checkEvents(renderWindow, event);
                    this->purpleChipButton.checkEvents(renderWindow, event);
                    this->yellowChipButton.checkEvents(renderWindow, event);
                }
                else {
                    this->hitButton.checkEvents(renderWindow, event); /// de pus in functie de update
                    this->doubleDownButton.checkEvents(renderWindow, event); /// de pus in functie de update
                    this->standButton.checkEvents(renderWindow, event);
                    this->splitButton.checkEvents(renderWindow, event);
                    this->insuranceButton.checkEvents(renderWindow, event);
                    this->restartButton.checkEvents(renderWindow, event);
                }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) { // enter pentru a da bet
                playerHasBetted = true;
            }

        }
        Color darkGreen(0, 100, 0); // This will create a red color - e verde

        renderWindow.clear(darkGreen);
        this->update(playerHasBetted); /// logica jocului
        this->render(renderWindow, playerHasBetted); /// desenare
        renderWindow.display();
    }
}


TextureManager Card::textureManager;
TextureManager ChipButton::textureManager;
TextureManager Hand::textureManager;
TextureManager Game::textureManager;



extern "C" {
    __declspec(dllexport) const char* get_game_state() {
        // Your code to get the game state goes here.
        // This is just a placeholder.
        return "game state";
    }
}


int main()
{

    Card::textureManagerLoadCardTextures(); /// incarcare texturi
    ChipButton::textureManagerLoadChipTextures(); /// incarcare texturi
    Hand::textureManagerLoadFont(); /// incarcare font
    Game::textureManagerLoadFont(); /// incarcare font

    vector<Participant*> participants;

    participants.resize(2);

    /// Player(string name, int age, int chips[7], float balance, float bet, float initialBet, float positionX, float positionY)


    string playerName = "Player";
    string dealerName = "Dealer";


    int playerChips[7] = { 0, 0, 0, 0, 0, 0, 0 };
    int dealerChips[7] = { 0, 0, 0, 0, 0, 0, 0 };
    Player* player = new Player(playerName, 18, playerChips, 1000, 0, 0, 0, 0);
    Dealer* dealer = new Dealer(dealerName, 18, dealerChips, 0, 0, 0, 0, 0);

    participants[1] = player;
    participants[0] = dealer;

    Game game(1, true, participants);

    RenderWindow window(VideoMode(1280, 720), "SFML window");
    window.setFramerateLimit(60);

    game.runtime(window);




    ///player->getHands()[0].render(RenderWindow); exemplu const - a fost modificat de la const e mai complicat


    ///Button(float x, float y, float width, float height, Color color, Color hoverColor, function<void()> onClickFunction, const Font & font, const string & text);


    /// test pentru diamant - merge !!!


    /*
    DealerPlayer dealerPlayer;
    cin>>dealerPlayer;
    cout<<dealerPlayer;
    */


    return 0;
}





