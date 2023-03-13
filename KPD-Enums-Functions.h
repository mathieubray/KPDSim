#ifndef ENUMSFUNCTIONS_H
#define ENUMSFUNCTIONS_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <ctime>

/* Enums */

// Simulation Specifications
enum KPDOptimizationScheme { CYCLES_AND_CHAINS, CYCLES_AND_CHAINS_WITH_FALLBACKS, LOCALLY_RELEVANT_SUBSETS };
enum KPDUtilityScheme { UTILITY_TRANSPLANTS, UTILITY_FIVE_YEAR_SURVIVAL, UTILITY_TEN_YEAR_SURVIVAL, UTILITY_TRANSPLANT_DIFFICULTY, UTILITY_RANDOM };
enum KPDDonorAssignment { DONOR_ASSIGNMENT_PAIRED, DONOR_ASSIGNMENT_RANDOM };
enum KPDTimeline { TIMELINE_FIXED, TIMELINE_CONTINUOUS };
enum KPDMatchFailure { MATCH_FAILURE_PRA_BASED, MATCH_FAILURE_RANDOM };

// Characteristics
enum KPDRelation {
	RELATION_PARENT, RELATION_NDD, RELATION_LIVING_DECEASED, RELATION_NON_DOMINO_THERAPEUTIC,
	RELATION_CHILD, RELATION_TWIN, RELATION_SIBLING, RELATION_HALF_SIBLING, RELATION_RELATIVE,
	RELATION_SPOUSE, RELATION_PARTNER, RELATION_PAIRED_DONATION, RELATION_OTHER_UNRELATED, RELATION_UNSPECIFIED };
enum KPDBloodType { BT_O, BT_A, BT_B, BT_AB };
enum KPDRace { RACE_WHITE, RACE_BLACK, RACE_HISPANIC, RACE_OTHER };
enum KPDInsurance { INSURANCE_PUBLIC, INSURANCE_PRIVATE, INSURANCE_OTHER };

// Node Properties
enum KPDStatus{ STATUS_ACTIVE, STATUS_INACTIVE, STATUS_WITHDRAWN };
enum KPDTransplant { TRANSPLANT_NO, TRANSPLANT_IN_PROGRESS, TRANSPLANT_YES };
enum KPDNodeType { PAIR, NDD, BRIDGE };

// Match Properties
enum KPDCrossmatch { CROSSMATCH_SUCCESSFUL, CROSSMATCH_O_DONOR_TO_NON_O_CANDIDATE, 
	CROSSMATCH_REQUIRES_DESENSITIZATION, CROSSMATCH_REQUIRES_DESENSITIZATION_AND_O_TO_NON_O, 
	CROSSMATCH_FAILED_HLA, CROSSMATCH_FAILED_BT, CROSSMATCH_FAILED_LAB };

// Output
enum KPDOutputFileType { OUTPUT_ARRANGEMENT_LIST, OUTPUT_TRANSPLANT_LIST, OUTPUT_POPULATION_LIST, OUTPUT_SIMULATION_LOG };


/* Functions */

namespace KPDFunctions {

	// Retrieve the index associated with the discrete sampling of a vector
	inline int retrieveDiscreteSampleIndex(double prob, std::vector<double> & probs) {

		int n = (int)probs.size();
		int outcome = 0;

		while (outcome + 1 < n && prob > probs[outcome]) {
			prob -= probs[outcome];
			outcome++;
		}
		return outcome;
	}

	// Assign flags to each element of a vector
	inline int setFlags(int value, std::vector<int> &flagVector) {

		//Starts at index 1
		int position = 1;
		int numberOfFlags = 0;
		while (value != 0) {
			int flag = value % 2;
			if (flag == 1) {
				numberOfFlags++;
				flagVector[position] = 1;
			}
			value = value / 2;
			position++;
		}

		return numberOfFlags;
	}

	// Truncate value to within a certain range
	inline double truncateValue(double value, double min, double max) {

		double newValue = value;
		if (value > max) {
			newValue = max;
		}
		if (value < min) {
			newValue = min;
		}

		return newValue;
	}


	// String Functions

	inline std::string intToString(int number) {
		std::stringstream stream;
		stream << number;
		return stream.str();
	}

	inline std::string boolToYesNo(bool flag) {
		if (flag) {
			return "Yes";
		}
		else {
			return "No";
		}
	}

	inline std::string boolToMaleFemale(bool male) {
		if (male) {
			return "Male";
		}
		else {
			return "Female";
		}
	}
	
	inline std::string boolToSuccessFailure(bool result) {
		if (result) {
			return "Success";
		}
		else {
			return "Failure";
		}
	}

	inline std::string boolToTF(bool result) {
		if (result) {
			return "T";
		}
		else {
			return "F";
		}
	}

	
	// Enum Converters

	inline std::string optimizationSchemeToString(KPDOptimizationScheme type) {
		if (type == CYCLES_AND_CHAINS) {
			return "Cycles and Chains";
		}
		else if (type == CYCLES_AND_CHAINS_WITH_FALLBACKS) {
			return "Cycles and Chains with Fallbacks";
		}
		else if (type == LOCALLY_RELEVANT_SUBSETS) {
			return "Locally Relevant Subsets";
		}
		else {
			return "Unspecified";
		}
	}

	inline std::string utilitySchemeToString(KPDUtilityScheme scheme) {
		if (scheme == UTILITY_TRANSPLANTS) {
			return "# Of Transplants";
		}
		else if (scheme == UTILITY_FIVE_YEAR_SURVIVAL) {
			return "5-Year Survival";
		}
		else if (scheme == UTILITY_TEN_YEAR_SURVIVAL) {
			return "10-Year Survival";
		}
		else if (scheme == UTILITY_TRANSPLANT_DIFFICULTY) {
			return "Difficult-to-Transplant Candidates";
		}
		else if (scheme == UTILITY_RANDOM) {
			return "Random Utility Assignment";
		}
		else {
			return "Unspecified";
		}
	}

	inline std::string donorAssignmentToString(KPDDonorAssignment scheme) {
		if (scheme == DONOR_ASSIGNMENT_PAIRED) {
			return "Paired Donor";
		}
		else if (scheme == DONOR_ASSIGNMENT_RANDOM) {
			return "Randomly Generated Donor";
		}
		else {
			return "Unspecified";
		}
	}


	inline std::string timelineToString(KPDTimeline timeline) {
		if (timeline == TIMELINE_FIXED) {
			return "Fixed Match Runs";
		}
		else if (timeline == TIMELINE_CONTINUOUS) {
			return "Continuous Timeline";
		}
		else {
			return "Unspecified";
		}
	}

	
	inline std::string matchFailureToString(KPDMatchFailure scheme) {
		if (scheme == MATCH_FAILURE_PRA_BASED) {
			return "Match Failure Probability PRA Based";
		}
		else if (scheme == MATCH_FAILURE_RANDOM) {
			return "Random Match Failure Probability";
		}
		else {
			return "Unspecified";
		}
	}

	inline std::string relationToString(KPDRelation relation) {
		if (relation == RELATION_PARENT) {
			return "Parent";
		}
		else if (relation == RELATION_NDD) {
			return "Non-Directed Donor";
		}
		else if (relation == RELATION_LIVING_DECEASED) {
			return "Living/Decased Donor";
		}
		else if (relation == RELATION_NON_DOMINO_THERAPEUTIC) {
			return "Non-Domino Therapeutic Donor";
		}
		else if (relation == RELATION_CHILD) {
			return "Child";
		}
		else if (relation == RELATION_TWIN) {
			return "Twin";
		}
		else if (relation == RELATION_SIBLING) {
			return "Sibling";
		}
		else if (relation == RELATION_HALF_SIBLING) {
			return "Half-Sibling";
		}
		else if (relation == RELATION_RELATIVE) {
			return "Relative";
		}
		else if (relation == RELATION_SPOUSE) {
			return "Spouse";
		}
		else if (relation == RELATION_PARTNER) {
			return "Partner";
		}
		else if (relation == RELATION_PAIRED_DONATION) {
			return "Paired Donation";
		}
		else if (relation == RELATION_OTHER_UNRELATED) {
			return "Other Unrelated Donor";
		}
		else if (relation == RELATION_UNSPECIFIED) {
			return "Unspecified";
		}
		else {
			return "Unspecified";
		}
	}

	inline std::string bloodTypeToString(KPDBloodType bloodType) {
		if (bloodType == BT_O) {
			return "O";
		}
		else if (bloodType == BT_A) {
			return "A";
		}
		else if (bloodType == BT_B) {
			return "B";
		}
		else if (bloodType == BT_AB) {
			return "AB";
		}
		else {
			return "Unspecified";
		}
	}

	inline std::string raceToString(KPDRace race) {
		if (race == RACE_WHITE) {
			return "White";
		}
		else if (race == RACE_BLACK) {
			return "Black";
		}
		else if (race == RACE_HISPANIC) {
			return "Hispanic";
		}
		else if (race == RACE_OTHER) {
			return "Other";
		}
		else {
			return "Unspecified";
		}
	}

	inline std::string insuranceToString(KPDInsurance insurance) {
		if (insurance == INSURANCE_PUBLIC) {
			return "Public Primary Payer";
		}
		else if (insurance == INSURANCE_PRIVATE) {
			return "Private Primary Payer";
		}
		else if (insurance == INSURANCE_OTHER) {
			return "Other Insurance";
		}
		else {
			return "Unspecified";
		}
	}

	inline std::string statusToString(KPDStatus state) {
		if (state == STATUS_ACTIVE) {
			return "Active";
		}
		else if (state == STATUS_INACTIVE) {
			return "Inactive";
		}
		else if (state == STATUS_WITHDRAWN) {
			return "Withdrawn";
		}
		else {
			return "Unspecified";
		}
	}

	inline std::string transplantToString(KPDTransplant state) {
		if (state == TRANSPLANT_NO) {
			return "Not Transplanted";
		}
		else if (state == TRANSPLANT_IN_PROGRESS) {
			return "In Progress";
		}
		else if (state == TRANSPLANT_YES) {
			return "Transplanted";
		}
		else {
			return "Unspecified";
		}
	}

	inline std::string nodeTypeToString(KPDNodeType type) {
		if (type == PAIR) {
			return "Pair";
		}
		else if (type == NDD) {
			return "NDD";
		}
		else if (type == BRIDGE) {
			return "Bridge Donor";
		}
		else {
			return "Unspecified";
		}
	}

	inline std::string crossmatchToString(KPDCrossmatch result) {
		if (result == CROSSMATCH_SUCCESSFUL) { 
			return "Successful Crossmatch"; 
		}
		else if (result == CROSSMATCH_O_DONOR_TO_NON_O_CANDIDATE) { 
			return "O Donor to Non-O Candidate"; 
		}
		else if (result == CROSSMATCH_REQUIRES_DESENSITIZATION) { 
			return "Requires Desensitization"; 
		}
		else if (result == CROSSMATCH_REQUIRES_DESENSITIZATION_AND_O_TO_NON_O) {
			return "Requires Desensitization and O Donor to Non-O Candidate";
		}
		else if (result == CROSSMATCH_FAILED_HLA) { 
			return "Failed Crossmatch (Based on HLA)"; 
		}
		else if (result == CROSSMATCH_FAILED_BT) { 
			return "Failed Crossmatch (Based on BT)";
		}
		else if (result == CROSSMATCH_FAILED_LAB) {
			return "Failed Crossmatch (Lab Crossmatch)";
		}
		else { 
			return "Unspecified"; 
		}
	}

	inline std::string outputFileTypeToString(KPDOutputFileType type) {
		if (type == OUTPUT_ARRANGEMENT_LIST) {
			return "Arrangement List";
		}
		else if (type == OUTPUT_TRANSPLANT_LIST) {
			return "Transplant List";
		}
		else if (type == OUTPUT_POPULATION_LIST) {
			return "Population List";
		}
		else if (type == OUTPUT_SIMULATION_LOG) {
			return "Simulation Log";
		}
		else {
			return "Unspecified";
		}
	}

	inline KPDOptimizationScheme stringToOptimizationScheme(std::string arrangementType) {
		KPDOptimizationScheme type = CYCLES_AND_CHAINS;
		if (arrangementType.compare("CYCLES_AND_CHAINS_WITH_FALLBACKS") == 0) { type = CYCLES_AND_CHAINS_WITH_FALLBACKS; }
		else if (arrangementType.compare("LOCALLY_RELEVANT_SUBSETS") == 0) { type = LOCALLY_RELEVANT_SUBSETS;  }
		
		return type;
	}

	inline KPDUtilityScheme stringToUtilityScheme(std::string utilityScheme) {
		KPDUtilityScheme scheme = UTILITY_TRANSPLANTS;
		if (utilityScheme.compare("UTILITY_FIVE_YEAR_SURVIVAL") == 0) { scheme = UTILITY_FIVE_YEAR_SURVIVAL; }
		else if (utilityScheme.compare("UTILITY_TEN_YEAR_SURVIVAL") == 0) { scheme = UTILITY_TEN_YEAR_SURVIVAL; }
		else if (utilityScheme.compare("UTILITY_TRANSPLANT_DIFFICULTY") == 0) { scheme = UTILITY_TRANSPLANT_DIFFICULTY; }
		else if (utilityScheme.compare("UTILITY_RANDOM") == 0) { scheme = UTILITY_RANDOM;  }

		return scheme;
	}

	inline KPDDonorAssignment stringToDonorAssignment(std::string donorAssignmentScheme) {
		KPDDonorAssignment scheme = DONOR_ASSIGNMENT_PAIRED;
		if (donorAssignmentScheme.compare("DONOR_ASSIGNMENT_RANDOM") == 0) { scheme = DONOR_ASSIGNMENT_RANDOM; }

		return scheme;
	}

	inline KPDTimeline stringToTimeline(std::string timeline) {
		KPDTimeline scheme = TIMELINE_FIXED;
		if (timeline.compare("TIMELINE_CONTINUOUS") == 0) { scheme = TIMELINE_CONTINUOUS; }

		return scheme;
	}	

	inline KPDMatchFailure stringToMatchFailure(std::string failureScheme) {
		KPDMatchFailure scheme = MATCH_FAILURE_PRA_BASED;
		if (failureScheme.compare("MATCH_FAILURE_RANDOM") == 0) { scheme = MATCH_FAILURE_RANDOM; }

		return scheme;
	}

	inline KPDRelation stringToRelation(std::string relation) {
		KPDRelation relationToCandidate = RELATION_UNSPECIFIED;
		if (relation.compare("Parent") == 0) { relationToCandidate = RELATION_PARENT; }
		else if (relation.compare("NDD") == 0) { relationToCandidate = RELATION_NDD; }
		else if (relation.compare("Living/Deceased") == 0) { relationToCandidate = RELATION_LIVING_DECEASED; }
		else if (relation.compare("Non-Domino Therapeutic") == 0) { relationToCandidate = RELATION_NON_DOMINO_THERAPEUTIC; }
		else if (relation.compare("Child") == 0) { relationToCandidate = RELATION_CHILD; }
		else if (relation.compare("Twin") == 0) { relationToCandidate = RELATION_TWIN; }
		else if (relation.compare("Sibling") == 0) { relationToCandidate = RELATION_SIBLING; }
		else if (relation.compare("Half-Sibling") == 0) { relationToCandidate = RELATION_HALF_SIBLING; }
		else if (relation.compare("Relative") == 0) { relationToCandidate = RELATION_RELATIVE; }
		else if (relation.compare("Spouse") == 0) { relationToCandidate = RELATION_SPOUSE; }
		else if (relation.compare("Partner") == 0) { relationToCandidate = RELATION_PARTNER; }
		else if (relation.compare("Paired Donation") == 0) { relationToCandidate = RELATION_PAIRED_DONATION; }
		else if (relation.compare("Other Unrelated") == 0) { relationToCandidate = RELATION_OTHER_UNRELATED; }

		return relationToCandidate;
	}

	inline KPDBloodType stringToBloodType(std::string bt) {
		KPDBloodType bloodtype = BT_O;
		if (bt.compare("A") == 0) { bloodtype = BT_A; }
		else if (bt.compare("B") == 0) { bloodtype = BT_B; }
		else if (bt.compare("AB") == 0) { bloodtype = BT_AB; }

		return bloodtype;
	}

	inline KPDRace stringToRace(std::string raceString) {
		KPDRace race = RACE_WHITE;
		if (raceString.compare("RACE_BLACK") == 0) { race = RACE_BLACK; }
		else if (raceString.compare("RACE_HISPANIC") == 0) { race = RACE_HISPANIC; }
		else if (raceString.compare("RACE_OTHER") == 0) { race = RACE_OTHER; }

		return race;
	}

	inline KPDInsurance stringToInsurance(std::string insuranceString) {
		KPDInsurance insurance = INSURANCE_PUBLIC;
		if (insuranceString.compare("INSURANCE_PRIVATE") == 0) { insurance = INSURANCE_PRIVATE; }
		else if (insuranceString.compare("INSURANCE_OTHER") == 0) { insurance = INSURANCE_OTHER; }

		return insurance;
	}

	inline KPDStatus stringToUnderlyingStatus(std::string underlyingStatus) {
		KPDStatus status = STATUS_ACTIVE;
		if (underlyingStatus.compare("STATUS_INACTIVE") == 0) { status = STATUS_INACTIVE; }
		else if (underlyingStatus.compare("STATUS_WITHDRAWN") == 0) { status = STATUS_WITHDRAWN; }

		return status;
	}

	inline KPDTransplant stringToTransplantationStatus(std::string transplantationStatus) {
		KPDTransplant status = TRANSPLANT_NO;
		if (transplantationStatus.compare("TRANSPLANT_IN_PROGRESS") == 0) { status = TRANSPLANT_IN_PROGRESS; }
		else if (transplantationStatus.compare("TRANSPLANT_YES") == 0) { status = TRANSPLANT_YES; }

		return status;
	}

	inline KPDNodeType stringToNodeType(std::string nodeType) {
		KPDNodeType type = PAIR;
		if (nodeType.compare("NDD") == 0) { type = NDD; }
		else if (nodeType.compare("BRIDGE") == 0) { type = BRIDGE; }

		return type;
	}

	inline KPDCrossmatch stringToCrossmatchResult(std::string result) {
		KPDCrossmatch crossmatchResult = CROSSMATCH_SUCCESSFUL;
		if (result.compare("CROSSMATCH_O_DONOR_TO_NON_O_CANDIDATE") == 0) { crossmatchResult = CROSSMATCH_O_DONOR_TO_NON_O_CANDIDATE; }
		else if (result.compare("CROSSMATCH_REQUIRES_DESENSITIZATION") == 0) { crossmatchResult = CROSSMATCH_REQUIRES_DESENSITIZATION; }
		else if (result.compare("CROSSMATCH_REQUIRES_DESENSITIZATION_AND_O_TO_NON_O") == 0) { crossmatchResult = CROSSMATCH_REQUIRES_DESENSITIZATION_AND_O_TO_NON_O; }
		else if (result.compare("CROSSMATCH_FAILED_HLA") == 0) { crossmatchResult = CROSSMATCH_FAILED_HLA; }
		else if (result.compare("CROSSMATCH_FAILED_BT") == 0) { crossmatchResult = CROSSMATCH_FAILED_BT; }
		else if (result.compare("CROSSMATCH_FAILED_LAB") == 0) { crossmatchResult = CROSSMATCH_FAILED_LAB; }

		return crossmatchResult;
	}

	inline KPDOutputFileType stringToOutputFileType(std::string fileType) {
		KPDOutputFileType type = OUTPUT_ARRANGEMENT_LIST;
		if (fileType.compare("OUTPUT_TRANSPLANT_LIST") == 0) { type = OUTPUT_TRANSPLANT_LIST; }
		else if (fileType.compare("OUTPUT_SIMULATION_LOG") == 0) { type = OUTPUT_SIMULATION_LOG; }
		
		return type;
	}

}

#endif