#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LOG_FILE "password_log.txt"

// Function declarations
int evaluatePassword(const char *password);
void giveSuggestions(const char *password);
void logResult(const char *password, int score);

int main() {
    char *password;
    int length;

    printf("Enter password length: ");
    scanf("%d", &length);

    // Dynamic memory allocation (pointer use)
    password = (char *)malloc((length + 1) * sizeof(char));
    if (password == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter your password: ");
    scanf("%s", password);

    int score = evaluatePassword(password);

    printf("\nPassword Strength Score: %d/5\n", score);

    if (score < 4) {
        printf("\nPassword is WEAK. Suggestions:\n");
        giveSuggestions(password);
    } else {
        printf("\nPassword is STRONG.\n");
    }

    // Log result into file
    logResult(password, score);

    free(password);
    return 0;
}

// Evaluate password strength out of 5
int evaluatePassword(const char *password) {
    int score = 0;
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;

    int len = strlen(password);

    // Length check
    if (len >= 8) score++;

    // Check character types
    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i])) hasUpper = 1;
        else if (islower(password[i])) hasLower = 1;
        else if (isdigit(password[i])) hasDigit = 1;
        else hasSpecial = 1;
    }

    if (hasUpper) score++;
    if (hasLower) score++;
    if (hasDigit) score++;
    if (hasSpecial) score++;

    return score;
}

//Yash code below
void giveSuggestions(const char *password) {
    int len = strlen(password);
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;

    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i])) hasUpper = 1;
        else if (islower(password[i])) hasLower = 1;
        else if (isdigit(password[i])) hasDigit = 1;
        else hasSpecial = 1;
    }

    if (len < 8)
        printf("- Increase password length to at least 8 characters.\n");
    if (!hasUpper)
        printf("- Add at least one uppercase letter (A-Z).\n");
    if (!hasLower)
        printf("- Add at least one lowercase letter (a-z).\n");
    if (!hasDigit)
        printf("- Include digits (0-9).\n");
    if (!hasSpecial)
        printf("- Add special characters (!, @, #, $, etc.).\n");
}





// Log results into a file
void logResult(const char *password, int score) {
    FILE *file = fopen(LOG_FILE, "a");
    if (file == NULL) {
        printf("Error opening log file!\n");
        return;
    }

    fprintf(file, "Password: %s | Strength Score: %d/5\n", password, score);
    fclose(file);
}
