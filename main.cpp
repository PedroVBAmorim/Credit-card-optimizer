#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

struct CreditCard {
    string name;

    double annualFee;
    double signupBonusPoints;
    double signupBonusPointValue;
    double rateGeneral;
    double rateTravel;
    double rateDining;
    double rateGrocery;
    double rewardPointValue;
    double perkValuePerYear;
    int    numTravelPartners;
    double foreignTxFeeRate;
  };
struct UserProfile {
    double spendTravel;
    double spendDining;
    double spendGrocery;
    double spendOther;
    double foreignSpendRatio;
    double wSignup;
    double wRewards;
    double wPerks;
    double wFees;
    double wPartners;
    double wFxFees;
};

double signupBonusValue( const CreditCard &card ) {
    return card.signupBonusPoints * card.signupBonusPointValue;
}
double ongoingRewardsValue( const CreditCard &card, const UserProfile &user ) {
    double travelPts= user.spendTravel  * card.rateTravel;
    double diningPts= user.spendDining  * card.rateDining;
    double groceryPts= user.spendGrocery * card.rateGrocery;
    double otherPt = user.spendOther * card.rateGeneral;
    double totalPts = travelPts + diningPts + groceryPts + otherPts;
    return totalPts * card.rewardPointValue;
}
double foreignTxFees( const CreditCard &card, const UserProfile &user ) {
    double totalSpend = user.spendTravel + user.spendDining + user.spendGrocery +user.spendOther;
    double foreignSpend = totalSpend * user.foreignSpendRatio;
    return foreignSpend * card.foreignTxFeeRate;
}
double cardScore( const CreditCard &card, const UserProfile &user ) {
    double bonus  = signupBonusValue(card);
    double rewards= ongoingRewardsValue(card, user);
    double fx= foreignTxFees(card, user);
    double score = 0.0;
    score += user.wSignup   * ( bonus   / 1000.0 );
    score +=user.wRewards * ( rewards / 1000.0 );
    score += user.wPerks * ( card.perkValuePerYear / 1000.0 );
    score -= user.wFees    * ( card.annualFee / 1000.0 );
    score -= user.wFxFees  * ( fx / 1000.0 );
    score += user.wPartners * ( card.numTravelPartners / 10.0 );
    return score;
}
const CreditCard *bestCardForUser( const vector<CreditCard> &cards,const UserProfile &user ) {
    const CreditCard *best = nullptr;
    double bestScore = -numeric_limits<double>::infinity();
    for( auto &c : cards ) {
        double s = cardScore( c, user );
        if( s > bestScore ) {
            bestScore = s;
            best = &c;
         }
    }
    return best;
}
int main() {
    vector<CreditCard> cards = {
        { "TravelPlus Preferred",
          95.0,
          60000, 0.0125,
          1.0, 3.0, 2.0, 2.0,
          0.01,
          250.0,
          15,
          0.0 },

        { "CashBack Everyday",
          0.0,
          20000, 0.01,
          1.5, 1.5, 3.0, 2.0,
          0.01,
          50.0,
          0,
          0.03 },

        { "Premium Traveler Elite",
          550.0,
          100000, 0.015,
          1.0, 5.0, 3.0, 1.0,
          0.015,
          600.0,
          25,
          0.0 }
    };
    UserProfile user;
    cout << "credit card optimizer\n\n";
    cout << "annual spend estimates\n";
    cout << "  travel:  ";
    cin  >> user.spendTravel;
    cout << "  dining:  ";
    cin  >> user.spendDining;
    cout << "  grocery: ";
    cin  >> user.spendGrocery;
    cout << "  other:   ";
    cin  >> user.spendOther;
    cout << "fraction of spend that is foreign (0 - 1): ";
    cin  >> user.foreignSpendRatio;
    user.wSignup   = 1.0;
    user.wRewards  = 2.0;
    user.wPerks    = 1.0;
    user.wFees     = 1.5;
    user.wPartners = 0.5;
    user.wFxFees   = 1.0;
    const CreditCard *best = bestCardForUser( cards, user );
    if( !best ) {cout << "\nno cards\n";
    return 0;
    }
    double bonus   = signupBonusValue( *best );
    double rewards = ongoingRewardsValue( *best, user );
    double fx      = foreignTxFees( *best, user );
    double netYear = bonus + rewards + best->perkValuePerYear- best->annualFee - fx;
    cout << "\nrecommended card: " << best->name << "\n\n";
    cout << "first-year estimate\n";
    cout << "  signup bonus: " << bonus << "\n";
    cout << "  rewards:      " << rewards << "\n";
    cout << "  perks:        " << best->perkValuePerYear << "\n";
    cout << "  annual fee:  -" << best->annualFee << "\n";
    cout << "  fx fees:     -" << fx << "\n";
    cout << "  -------------------------\n";
    cout << "  net:          " << netYear << "\n";
    return 0;
}
