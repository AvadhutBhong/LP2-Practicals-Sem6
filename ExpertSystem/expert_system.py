# This is a simple medical expert system that diagnoses common illnesses
# based on user-reported symptoms. It uses a set of rules to determine
# the most likely condition and provides a recommendation.
# The system is designed to be user-friendly and interactive, asking the user   
# for symptoms and providing a diagnosis based on the input.
# The system is not a substitute for professional medical advice and should not be used for serious health issues.
def rule_flu(symptoms):
    return "fever" in symptoms and "cough" in symptoms and "fatigue" in symptoms

def rule_covid(symptoms):
    return "fever" in symptoms and "cough" in symptoms and "breathing_difficulty" in symptoms

def rule_cold(symptoms):
    return "cough" in symptoms and "fever" not in symptoms

def rule_unknown(symptoms):
    return True  # fallback rule


#Diagnosis function that uses the rules to determine the condition
# This function will check the symptoms against the rules defined above
# and return a diagnosis based on the rules that match the symptoms
def diagnose(symptoms):
    if rule_covid(symptoms):
        return "You may have COVID-19. Get tested and isolate yourself."
    elif rule_flu(symptoms):
        return "You may have Flu. Please consult a doctor."
    elif rule_cold(symptoms):
        return "You might have a Common Cold. Rest and drink fluids."
    else:
        return "Symptoms unclear. Please consult a doctor."


# Function to get symptoms from the user
# This function will ask the user a series of questions to determine their symptoms
def get_symptoms():
    symptoms = []
    questions = {
        "fever": "Do you have fever?",
        "cough": "Do you have cough?",
        "fatigue": "Do you feel fatigue?",
        "breathing_difficulty": "Do you have difficulty breathing?",
        "headache": "Do you have headache?"
    }
    for symptom, question in questions.items():
        ans = input(question + " (yes/no): ").strip().lower()
        if ans == "yes":
            symptoms.append(symptom)
    return symptoms


# Main function to run the expert system
# This function will print the title, get symptoms from the user,
# and then call the diagnose function to get the result
# Finally, it will print the diagnosis result to the user
def main():
    print("=== Medical Expert System ===")
    symptoms = get_symptoms()
    result = diagnose(symptoms)
    print("\nDiagnosis Result:")
    print(result)

if __name__ == "__main__":
    main()
