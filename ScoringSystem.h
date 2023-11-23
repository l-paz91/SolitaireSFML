// -----------------------------------------------------------------------------
#ifndef ScoringSystem_H
#define ScoringSystem_H
// -----------------------------------------------------------------------------

//--INCLUDES--//


// -----------------------------------------------------------------------------

/*
	// ---- Scoring System ----//

	Scoring system breakdown:
	1. Moving Cards to Foundation:
		+ 10 points for each card moved to foundation
	2. Moving Cards from the Deck:
		+ 5 points for turning over a face-down card in the tableau
		+ 5 points for each card moved from the deck to the tableau
		- 15 points for re-flipping the deck (when the waste is put back into the stock)
	3. Waste to Tableau:
		+ 5 points for moving a card from the waste (face-up cards next to the deck) to the tableau.
	4. Waste to Foundation:
		+ 10 points for moving a card from the waste to the foundation.
	5. Tableau to Foundation:
		+ 10 points for moving a card from the tableau to the foundation.
	6. Turning over a Tableau Card:
		+ 5 points for turning over a face-down card in the tableau.
	7. Foundation to Tableau:
		- 15 points for moving a card from the foundation to the tableau.

*/

// -----------------------------------------------------------------------------

enum EScoringSystem
{
	eDEFAULT = 0,
	eFLIP_TABLEAU_CARD = 5,
	eCARD_TO_TABLEAU = 5,
	eWASTE_TO_TABLEAU = 5,
	eTABLEAU_CARD_FLIP = 5,
	eCARD_TO_FOUNDATION = 10,
	eWASTE_TO_FOUNDATION = 10,
	eTABLEAU_TO_FOUNDATION = 10,
	eFOUNDATION_TO_TABLEAU = -15,
	eREFLIP_WASTE = -15,
};


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !ScoringSystem_H