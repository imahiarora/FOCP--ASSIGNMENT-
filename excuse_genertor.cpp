#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>

// ---------------------------------------------------------------------------
// Validates that the name is non-empty and contains only letters and spaces.
// Written without range-based for loops (C++98 compatible).
// ---------------------------------------------------------------------------
bool isValidName(const std::string& name) {
    if (name.empty()) return false;

    bool hasLetter = false;
    for (std::size_t i = 0; i < name.size(); ++i) {
        unsigned char ch = static_cast<unsigned char>(name[i]);
        if (!std::isalpha(ch) && ch != ' ') return false;
        if (std::isalpha(ch)) hasLetter = true;
    }
    return hasLetter;
}

// ---------------------------------------------------------------------------
// Trims leading and trailing whitespace from a string (no lambdas).
// ---------------------------------------------------------------------------
std::string trim(const std::string& s) {
    std::size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start])))
        ++start;

    std::size_t end = s.size();
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1])))
        --end;

    return s.substr(start, end - start);
}

// ---------------------------------------------------------------------------
// Replaces every occurrence of {name} in the template with the actual name.
// ---------------------------------------------------------------------------
std::string fillTemplate(std::string tmpl, const std::string& name) {
    const std::string placeholder = "{name}";
    std::size_t pos = 0;
    while ((pos = tmpl.find(placeholder, pos)) != std::string::npos) {
        tmpl.replace(pos, placeholder.size(), name);
        pos += name.size();
    }
    return tmpl;
}

// ---------------------------------------------------------------------------
// Main
// ---------------------------------------------------------------------------
int main() {
    // Build the excuse list without initializer-list syntax (C++98 compatible)
    std::vector<std::string> excuses;
    excuses.push_back("Sorry, {name} couldn't submit the homework because a sudden power outage wiped out the entire document right before saving.");
    excuses.push_back("{name}'s dog discovered a hidden talent for shredding paper and chose the homework as its debut masterpiece.");
    excuses.push_back("Unfortunately, {name} was abducted by aliens last night. They returned safely this morning but the homework stayed aboard.");
    excuses.push_back("{name} completed every question, but accidentally emailed it to the pizza delivery app instead of the school portal.");
    excuses.push_back("A freak gust of wind swept through {name}'s window and carried the printed homework three blocks away; a search party is still active.");
    excuses.push_back("{name}'s little sibling mistook the assignment for a colouring book and the damage is, frankly, irreversible.");
    excuses.push_back("The family Wi-Fi developed sentience overnight and specifically blocked {name} from uploading anything academic.");
    excuses.push_back("{name} was halfway through the last problem when a neighbourhood cat sat on the keyboard and overwrote everything with 'mrrrrp'.");
    excuses.push_back("Tragically, {name} sneezed at the critical moment and the homework flew directly into a lit birthday cake.");
    excuses.push_back("{name} stored the file on a USB drive that was immediately swallowed by the vacuum cleaner during a surprise cleaning session.");
    excuses.push_back("A time-zone miscalculation led {name} to believe the deadline was actually tomorrow -- on the planet Mars.");
    excuses.push_back("{name} finished the homework but the printer ran out of ink on the very last line, which happened to be the most important one.");

    // Seed random number generator
    srand(static_cast<unsigned int>(time(0)));

    int totalExcuses  = 0;   // grand total across all students
    int totalStudents = 0;   // number of students served

    // ── Outer loop: one iteration per student ─────────────────────────────────
    while (true) {
        // -- Name input & validation ------------------------------------------
        std::string name;
        while (true) {
            std::cout << "\n=========================================\n";
            std::cout << "    Homework Excuse Generator v1.0\n";
            std::cout << "=========================================\n";
            std::cout << "Enter student name: ";
            std::getline(std::cin, name);

            std::string trimmed = trim(name);

            if (trimmed.empty()) {
                std::cerr << "\n[ERROR] Name cannot be empty. Please try again.\n";
                continue;
            }
            if (trimmed.size() > 50) {
                std::cerr << "\n[ERROR] Name is too long (max 50 characters). "
                             "You entered " << trimmed.size() << " characters. Please try again.\n";
                continue;
            }
            if (!isValidName(trimmed)) {
                std::cerr << "\n[ERROR] Name must contain only letters and spaces "
                             "(no numbers or special characters). Please try again.\n";
                continue;
            }

            name = trimmed;
            break;
        }

        ++totalStudents;
        int excusesForStudent = 0;

        // -- Inner loop: excuse replay for this student -----------------------
        while (true) {
            int index = rand() % static_cast<int>(excuses.size());
            std::string result = fillTemplate(excuses[index], name);

            ++excusesForStudent;
            ++totalExcuses;

            std::cout << "\n-----------------------------------------\n";
            std::cout << "  Excuse #" << excusesForStudent
                      << " for " << name << ":\n";
            std::cout << "-----------------------------------------\n";
            std::cout << result << "\n";
            std::cout << "-----------------------------------------\n";

            // Ask for another excuse for the same student
            std::string answer;
            while (true) {
                std::cout << "\nWould you like another excuse for " << name << "? (y/n): ";
                std::getline(std::cin, answer);

                if (answer == "y" || answer == "Y") {
                    break;                      // generate one more for same student
                } else if (answer == "n" || answer == "N") {
                    goto done_with_student;     // move on to next-student prompt
                } else {
                    std::cerr << "[ERROR] Invalid input. Please enter y or n.\n";
                }
            }
        }
        done_with_student:

        // -- Ask whether to serve another student -----------------------------
        std::string next;
        while (true) {
            std::cout << "\nGenerate excuse for another student? (y/n): ";
            std::getline(std::cin, next);

            if (next == "y" || next == "Y") {
                break;                          // outer loop: next student
            } else if (next == "n" || next == "N") {
                goto end_session;
            } else {
                std::cerr << "[ERROR] Invalid input. Please enter y or n.\n";
            }
        }
    }
    end_session:

    // ── Session summary ───────────────────────────────────────────────────────
    std::cout << "\n=========================================\n";
    std::cout << "           Session Summary\n";
    std::cout << "=========================================\n";
    std::cout << "  Students served : " << totalStudents << "\n";
    std::cout << "  Excuses generated: " << totalExcuses  << "\n";
    std::cout << "=========================================\n";
    std::cout << "Goodbye! Good luck to everyone!\n\n";

    return 0;
}