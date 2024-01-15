#include <iostream>
#include <vector>
#include <algorithm> 
#include <random>
#include "Card.hpp"    
#include "Player.hpp"
#include "Pack.hpp"
#include <fstream>

using namespace std;


class Game {
public:
  // Game(const std::vector<std::string>& playerNames, 
  // const std::vector<std::string>& playerTypes, int t, bool s,std::istream& pack_input)
  // :currentDealer(0), 
  // targetScore(t), team1score(0), team2score(0), shuf(s), playerup(0)
  // {
  //   for (int i = 0; i < playerNames.size(); i++) {
  //       players.push_back(Player_factory(playerNames[i], playerTypes[i]));
  //   }
  //   pack = Pack(pack_input);  
  // }
    Game(const std::vector<std::string>& playerNames, 
         const std::vector<std::string>& playerTypes, 
         const std::pair<int, bool>& config, 
         std::istream& pack_input)
        : currentDealer(0), 
          targetScore(config.first),  // first of the pair
          team1score(0), 
          team2score(0), 
          shuf(config.second),  // second of the pair
          playerup(0)
    {
        for (int i = 0; i < playerNames.size(); i++) {
            players.push_back(Player_factory(playerNames[i], playerTypes[i]));
        }
        pack = Pack(pack_input);  
    }
  void play() {
    int hand = 0;
    while(game_over()) {
      cout << "Hand "<< hand << endl;
      shuffle();
      deal();
      make_trump();
      play_hand();
      currentDealer = (currentDealer + 1) % 4;
      hand++;
      }
  }

  void cleanupPlayers() {
            for (Player* player : players) {
                delete player;
            }
            players.clear();
    }

private:
    std::vector<Player*> players;
    Pack pack;
    int currentDealer; 
    Card upcard;
    int targetScore;
    int team1score;
    int team2score;
    bool shuf;
    Suit trumpsuit;
    int playerup;

    void shuffle() {
      if (shuf) {
      pack.shuffle();
     } else {
      pack.reset();
     }
    }

    void deal() {
    cout << players[currentDealer]->get_name() << " deals" << endl;
    int index = (currentDealer + 1) % 4;
    int cardsToDeal[] = {3, 2, 3, 2, 2, 3, 2, 3};
    for (int j = 0; j < 8; j++) {
        for (int i = 0; i < cardsToDeal[j]; i++) {
            players[index]->add_card(pack.deal_one());
        }
        index = (index + 1) % 4;
    }
    upcard = pack.deal_one();
    cout << upcard << " turned up" << endl;
}

    void make_trump() {
      bool trumpChosen = false;
      bool isdealer = false;
    for (int i = 1; i <= 4; ++i) {
      if (i == 4) {
          isdealer = true;
        }
      if(players[(currentDealer + i) % 4]->make_trump(upcard, isdealer, 1, trumpsuit)){
            cout << players[(currentDealer + i) % 4]->get_name() 
            << " orders up " << trumpsuit << endl;
            playerup = (currentDealer + i) % 4;
            trumpChosen = true;
            break;
        } else {
          cout << players[(currentDealer + i) % 4]->get_name() << " passes" << endl;
        }
      }
      isdealer = false;
      if (trumpChosen) {
        players[currentDealer]->add_and_discard(upcard);
      }
      if (!trumpChosen) {
        for (int i = 1; i <= 4; ++i) {
            if (i == 4) {
              isdealer = true;
            }
  if (players[(currentDealer + i) % 4]->make_trump(upcard, isdealer, 2, trumpsuit)){
              cout << players[(currentDealer + i) % 4]->get_name() 
              << " orders up " << trumpsuit << endl;
              playerup = (currentDealer + i) % 4;
              trumpChosen = true;
              break;
            } else {
              cout << players[(currentDealer + i) % 4 ] -> get_name() 
              << " passes" << endl; 
            }
        }
      }
    }

  int play_single_trick(int leader) {
    std::cout << ""<< std::endl;
    std::vector<Card> currentHand;
    Card leadcard = players[leader]->lead_card(trumpsuit);
    currentHand.push_back(leadcard);
    cout << leadcard << " led by " << players[leader]->get_name() << endl;

    for (int i = 1; i < 4; ++i) {
        Card played = players[(leader + i) % 4]->play_card(leadcard, trumpsuit);
        currentHand.push_back(played);
        cout << played << " played by " << players[(leader + i) % 4]->get_name()<<endl;
    }

    int maxIn = 0;
    for (int i = 0; i < 4; i++) {
        if (Card_less(currentHand[maxIn], currentHand[i], currentHand[0], trumpsuit)) {
            maxIn = i;
        }
    }
    cout << players[(leader+maxIn)%4]->get_name() << " takes the trick" << endl;

    return (leader+maxIn)%4;
}

void play_hand() {
    int team1trick = 0;
    int leader = (currentDealer+1)%4;
    for (int j = 0; j < 5; j++) {
        leader = play_single_trick(leader);
        team1trick += (leader == 0 || leader == 2) ? 1 : 0;
    }
    std::cout << ""<< std::endl;
    if (team1trick > 2) {
        cout << players[0]->get_name() << " and " << players[2]->get_name() 
        << " win the hand" << endl;
        if (playerup % 2 == 0) {
            if (team1trick == 5) {
                team1score += 2;
                cout << "march!" << endl;
            } else {
                team1score += 1;
            }
        } else {
            team1score += 2;
            cout << "euchred!" << endl;
        }
    } else {
        cout << players[1]->get_name() << " and " << players[3]->get_name() 
        << " win the hand" << endl;
        if (playerup % 2 == 1) {
            if (team1trick == 0) { // Reverse for team 2
                team2score += 2;
                cout << "march!" << endl;
            } else {
                team2score += 1;
            }
        } else {
            team2score += 2;
            cout << "euchred!" << endl;
        }
    }

    cout << players[0]->get_name() << " and " << players[2]->get_name() 
    << " have " << team1score << " points" << endl;
    cout << players[1]->get_name() << " and " << players[3]->get_name() 
    << " have " << team2score << " points" << endl;
    cout << "" << endl;
}
   




    bool game_over() {
      if (team1score >= targetScore || team2score >= targetScore) {
        if (team1score > team2score) {
          cout << players[0]-> get_name() << " and " 
          << players[2]->get_name() << " win!" <<endl;
          return false;
        } else {
          cout << players[1]-> get_name() << " and " 
          << players[3]->get_name() << " win!" <<endl;
          return false;
        }
      }
      return true;
    }
};



int main(int argc, char **argv) {
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << " ";
    }
    std::cout << std::endl;
    
     if (argc != 12) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
        return 1;
    }
    ifstream packFile;
    packFile.open(argv[1]);
    if (!packFile.is_open()) {
        cout << "Error opening " << argv[1] << endl;
        return 1;
    }
    int pointsToWin = atoi(argv[3]);
    if (pointsToWin < 1 || pointsToWin > 100) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
        return 1;
    }

    string shuffleArg = argv[2];
    if (shuffleArg != "shuffle" && shuffleArg != "noshuffle") {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
        return 1;
    }
    bool shuffle = false;
    if (shuffleArg == "shuffle") {
      shuffle = true;
    }

    for (int i = 5; i <= 11; i += 2) {  
        string type = argv[i];
        if (type != "Simple" && type != "Human") {
            cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
                 << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
                 << "NAME4 TYPE4" << endl;
            return 1;
        }
    }

    std::vector<std::string> playerNames = {argv[4], argv[6], argv[8], argv[10]};
    std::vector<std::string> playerTypes = {argv[5], argv[7], argv[9], argv[11]};
    std::pair<int, bool> config(pointsToWin, shuffle);
    Game game(playerNames, playerTypes, config , packFile);
    game.play();

    game.cleanupPlayers();

    return 0;
}