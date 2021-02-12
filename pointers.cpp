// compile: g++ -std=c++11 -o pointers pointers.cpp
#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>

typedef struct Student
{
    int id;
    char *f_name;
    char *l_name;
    int n_assignments;
    double *grades;
} Student;

int promptInt(std::string message, int min, int max);
double promptDouble(std::string message, double min, double max);
void calculateStudentAverage(void *object, double *avg);

int main(int argc, char **argv)
{
    Student student;
    double average;

    student.f_name = new char[128];
    student.l_name = new char[128];

    // Sequence of user input -> store in fields of `student`
    std::cout << "Please enter the student's id number: ";
    std::cin >> student.id;
    std::cin.ignore();
    std::cout << "Please enter the student's first name: ";
    std::cin.getline(student.f_name, 128);
    std::cout << "Please enter the student's last name: ";
    std::cin.getline(student.l_name, 128);
    student.n_assignments = promptInt("Please enter how many assignments were graded: ", 1, 134217728);
    //loop to get assignment grades
    int i;
    student.grades = new double[student.n_assignments];
    for (i = 0; i < student.n_assignments; i++)
    {
        std::string message = "Please enter grade for assignment ";
        std::string i_as_string = std::to_string(i);
        message = message + i_as_string + ": ";
        student.grades[i] = promptDouble(message, 0, 1000);
    }
    average = 0;

    void *void_student = &student;

    calculateStudentAverage(void_student, &average);

    std::cout << "\n Student: " << student.f_name << " " << student.l_name << " [" << student.id << "] " << std::endl;
    std::cout << "   Average grade: ";
    std::cout << std::setprecision(1) << std::fixed << average << "\n"<< std::endl;

    // Call `CalculateStudentAverage(???, ???)`
    //CalculateStudentAverage(student, average);
    // Output `average`

    return 0;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid int
   max: maximum value to accept as a valid int
*/
int promptInt(std::string message, int min, int max)
{
    char *num_as_string; //holds user input
    num_as_string = new char[9];
    bool valid;
    //how many assignments were graded, taking user input storing it

    while (1)
    {
        std::cout << message;
        std::cin.getline(num_as_string, 1235);
        //std::cin.ignore();

        int i;
        valid = true; //initlize valid to true
        //loop through user input
        for (i = 0; i < strlen(num_as_string); i++)
        {
            //if something isnt a digit print error message and break
            if (!(isdigit(num_as_string[i])))
            {
                std::cout << "Sorry, I cannot understand your answer \n";
                valid = false;
                break;
            }
        }
        if (valid == true)
        {
            if ((std::atoi(num_as_string) < min) || (std::atoi(num_as_string) > max))
            {

                std::cout << "Sorry, I cannot understand your answer";
            }
            else
            {
                //if it gets to here is passed all tests, return user input
                return std::atoi(num_as_string);
                break;
            }
        }
    }

    // Code to prompt user for an int
    return 0;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid double
   max: maximum value to accept as a valid double
*/
double promptDouble(std::string message, double min, double max)
{
    // Code to prompt user for a double
    //loop for as long as they failed to put in a right data type
    char *double_as_string; //holds user input
    double_as_string = new char[10];
    bool valid;
    bool decimal_found;

    while (1)
    {
        std::cout << message;
        std::cin.getline(double_as_string, 1235);

        int i;
        valid = true; //initlize valid to true
        decimal_found = false;
        //loop through user input
        for (i = 0; i < strlen(double_as_string); i++)
        {
            //if there is a second decimal
            if ((double_as_string[i] == '.') && (decimal_found == true))
            {
                std::cout << "Sorry, I cannot understand your answer\n";
                valid = false;
                break;
            }
            else if (double_as_string[i] == '.')
            {
                decimal_found = true;
            }
            else if (!(isdigit(double_as_string[i]))) //if something isnt a digit print error message and break
            {
                std::cout << "Sorry, I cannot understand your answer \n";
                valid = false;
                break;
            }
        }
        if (valid == true)
        {
            double double_input;
            double_input = atof(double_as_string);
            if ((double_input < min) || (double_input >= max))
            {
                std::cout << "Sorry, I cannot understand your answer \n";
            }
            else
            {
                //if it gets to here is passed all tests, return user input
                return double_input;
                break;
            }
        }
    }
    return 0;
}

/*
   object: pointer to anything - your choice! (but choose something that will be helpful)
   avg: pointer to a double (can store a value here)
*/
void calculateStudentAverage(void *object, double *avg)
{
    // Code to calculate and store average grade
    Student *student = (Student *)object;
    double sum; //add to this and eventaully set average to equal this
    int i;
    int assignments = student->n_assignments;
    //double *grades_cast = new double[assignments];
    //grades_cast = (double*)student->grades;
    for (i = 0; i < assignments; i++)
    {
        sum += student->grades[i]; //add each grade to sum
    }
    *avg = sum / assignments; //divide sum by number of assignments
}
