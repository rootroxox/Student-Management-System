#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include <stdbool.h>

#pragma warning (disable:4996)
#define MAXCHAR 100
#define TEACHER_COURSE_LOAD 5
#define STUDENT_COURSE_LOAD 8
#define STUDENT_MAX_CREDITS 22

struct students {
    char studentNumber[50];
    char studentName[50];
    char studentSurname[50];
    char taken_courses[STUDENT_COURSE_LOAD][50];
    int number_of_taken_courses;
    int taken_credits;
};
struct courses {
    char courseCode[10];
    char courseName[50];
    int courseCredit;
    char who_is_taked[100][50];
    char who_is_taught[100];
    int number_of_taked_students;
    bool is_teaching;
};
struct lecturers {
    char regNumber[10];
    char regSurname[50];
    char regName[50];
    char courses_taught[TEACHER_COURSE_LOAD][50];
    int number_of_courses_taught;
};

/*
        PLEASE SEND ARGUMENTS IN THE FOLLOWING ORDER TO THE PROGRAM
        Ex: C:>DBMS students.txt lecturers.txt courses.txt commands.txt output.txt
*/

int main(int argc, char* argv[])
{
    int number_of_students = -1;
    int number_of_lecturers = -1;
    int number_of_courses = -1;

    char readed[MAXCHAR];
    char word1[100];
    char word2[100];
    char word3[100];

    FILE* fstudent = fopen(argv[1], "r"); // "r" for read
    FILE* flecturers = fopen(argv[2], "r"); // "r" for read
    FILE* fcourses = fopen(argv[3], "r"); // "r" for read
    FILE* fcommands = fopen(argv[4], "r"); // "r" for read
    FILE* foutput = fopen(argv[5], "a+"); // "a+" for append

    while (fgets(readed, MAXCHAR, fstudent) != NULL)
    {
        number_of_students++;                                                                 
    }

    struct students* student = malloc(number_of_students * sizeof(struct students));         

    rewind(fstudent);                                                                         

    int i = 0;
    int j = 0;
    int k = 0;

    while (fgets(readed, MAXCHAR, fstudent) != NULL)
    {
        readed[strcspn(readed, "\n")] = 0;
        if (sscanf(readed, "%s %s %s", word1, word2, word3) == 3)
        {
            strcpy(student[i].studentNumber, word1);
            strcpy(student[i].studentName, word2);                                         
            strcpy(student[i].studentSurname, word3);
            student[i].number_of_taken_courses = 0;
            student[i].taken_credits = 0;
            i++;
        }
    }

    while (fgets(readed, MAXCHAR, flecturers) != NULL)
    {
        number_of_lecturers++;                                                                 
    }

    struct lecturers* lecturer = malloc(number_of_lecturers * sizeof(struct lecturers));       

    rewind(flecturers);           //File refreshed for re-read!

    i = 0;

    while (fgets(readed, MAXCHAR, flecturers) != NULL)
    {
        readed[strcspn(readed, "\n")] = 0;
        if (sscanf(readed, "%s %s %s", word1, word2, word3) == 3)
        {
            strcpy(lecturer[i].regNumber, word1);
            strcpy(lecturer[i].regName, word2);                                             
            strcpy(lecturer[i].regSurname, word3);
            lecturer[i].number_of_courses_taught = 0;
            i++;
        }
    }

    while (fgets(readed, MAXCHAR, fcourses) != NULL)
    {
        number_of_courses++;                                                            
    }

    struct courses* course = malloc(number_of_courses * sizeof(struct courses));               

    rewind(fcourses);                                                                          

    i = 0;

    while (fgets(readed, MAXCHAR, fcourses) != NULL)
    {
        readed[strcspn(readed, "\n")] = 0;
        if (sscanf(readed, "%s %s %s", word1, word2, word3) == 3)
        {
            strcpy(course[i].courseCode, word1);
            strcpy(course[i].courseName, word2);                                                
            course[i].courseCredit = atoi(word3);
            strcpy(course[i].who_is_taught, " ");
            course[i].number_of_taked_students = 0;
            course[i].is_teaching = 0;
            i++;
        }
    }

    bool course_valid;
    bool lecturer_valid;
    bool student_valid;
    bool lecturer_course_load;
    bool student_course_load;
    bool student_taken_credits;
    bool who_is_taught;
    bool is_student_member_of_course;
    bool any_student_with_this_credit;


    while (fgets(readed, MAXCHAR, fcommands) != NULL)                                       
    {
        course_valid = 0;
        lecturer_valid = 0;
        student_valid = 0;
        lecturer_course_load = 0;
        student_course_load = 0;                                                              
        student_taken_credits = 0;
        who_is_taught = 0;
        is_student_member_of_course = 0;
        any_student_with_this_credit = 0;

        readed[strcspn(readed, "\n")] = 0;

        if (sscanf(readed, "%s %s %s", word1, word2, word3) == 3)
        {
            if (0 == strcmp("ASSIGN", word1))
            {
                for (i = 0; i < number_of_courses; i++)
                {
                    if (0 == strcmp(course[i].courseCode, word3))
                    {
                        course_valid = 1;
                        if (0 == course[i].is_teaching)            
                        {                                                         
                            who_is_taught = 1;
                        }
                        break;
                    }
                }
                for (j = 0; j < number_of_lecturers; i++)
                {
                    if (0 == strcmp(lecturer[j].regNumber, word2))
                    {
                        lecturer_valid = 1;
                        if (lecturer[j].number_of_courses_taught < TEACHER_COURSE_LOAD)      
                        {
                            lecturer_course_load = 1;
                        }
                        break;
                    }
                }

                fprintf(foutput, "%s %s \n%s", "Command: ", readed, "Result: \n");

                if (lecturer_course_load && lecturer_valid && course_valid && who_is_taught)
                {
                    strcpy(&lecturer[j].courses_taught[lecturer[j].number_of_courses_taught][0], word3);              
                    lecturer[j].number_of_courses_taught++;                        

                    if (0 == strcmp(course[i].courseCode, word3))
                    {
                        strcpy(course[i].who_is_taught, word2);                
                        course[i].is_teaching = 1;
                    }
                }
                else if (1 != (lecturer_course_load && lecturer_valid && course_valid && who_is_taught))
                {
                    if (lecturer_course_load != 1)
                        fprintf(foutput, "The teacher has reached the maximum number of lessons.\n");
                    if (lecturer_valid != 1)
                        fprintf(foutput, "The specified lecturer was not found.\n");
                    if (course_valid != 1)
                        fprintf(foutput, "The specified course was not found.\n");
                    if (who_is_taught != 1)
                        fprintf(foutput, "There is already a lecturer who teaches the lesson.\n");
                }
                fprintf(foutput, "\n");
            }
            else if (0 == strcmp("ADD", word1))
            {
                for (i = 0; i < number_of_courses; i++)
                {
                    if (0 == strcmp(course[i].courseCode, word3))
                    {
                        course_valid = 1;                                           
                        break;
                    }
                }
                for (j = 0; j < number_of_students; j++)
                {
                    if (0 == strcmp(student[j].studentNumber, word2))
                    {
                        student_valid = 1;                                               
                        if (student[j].number_of_taken_courses < STUDENT_COURSE_LOAD)
                        {
                            student_course_load = 1;                                     
                        }
                        if (student[j].taken_credits < STUDENT_MAX_CREDITS)
                        {
                            student_taken_credits = 1;                             
                        }
                        break;
                    }
                }

                fprintf(foutput, "%s %s \n%s", "Command: ", readed, "Result: \n");

                if (student_taken_credits && student_course_load && student_valid && course_valid)
                {
                    strcpy(&student[j].taken_courses[student[j].number_of_taken_courses][0], word3);                
                    student[j].number_of_taken_courses++;                                                  

                    strcpy(&course[i].who_is_taked[course[i].number_of_taked_students][0], word2);               
                    course[i].number_of_taked_students++;
                    student[j].taken_credits += course[i].courseCredit;
                }
                else if (1 != (student_taken_credits && student_course_load && student_valid && course_valid))
                {
                    if (student_taken_credits != 1)
                        fprintf(foutput, "The student has reached the maximum credit.\n");
                    if (student_course_load != 1)
                        fprintf(foutput, "The student has reached the maximum number of courses s/he can take.\n");
                    if (student_valid != 1)
                        fprintf(foutput, "The specified student was not found.\n");
                    if (course_valid != 1)
                        fprintf(foutput, "The specified course was not found.\n");
                    break;
                }
                fprintf(foutput, "\n");
            }
            else if (0 == strcmp("DROP", word1))
            {
                for (i = 0; i < number_of_courses; i++)
                {
                    if (0 == strcmp(course[i].courseCode, word3))
                    {
                        course_valid = 1;                                  
                        break;
                    }
                }
                for (i = 0; i < number_of_students; i++)
                {
                    if (0 == strcmp(student[i].studentNumber, word2))
                    {
                        student_valid = 1;                                  
                    }
                    for (j = 0; j < number_of_courses; j++)
                    {
                        if (0 == strcmp(&student[i].taken_courses[j][0], word3))
                        {
                            is_student_member_of_course = 1;                                 
                            break;
                        }
                        if (is_student_member_of_course)
                            break;
                    }
                    if (student_valid && is_student_member_of_course)
                        break;
                }
                fprintf(foutput, "%s %s \n%s", "Command: ", readed, "Result: \n");

                if ((student_valid && course_valid) && (is_student_member_of_course != 0))
                {
                    for (i = 0; i < number_of_courses; i++)
                    {
                        if (0 == strcmp(course[i].courseCode, word3))
                        {
                            for (j = 0; j < number_of_students; j++)
                            {
                                if (0 == strcmp(student[j].studentNumber, word2))
                                {
                                    for (k = 0; k < student[j].number_of_taken_courses; k++)
                                    {
                                        if (0 == strcmp(&student[j].taken_courses[k][0], word3))
                                        {
                                            student[j].taken_courses[k][0] = 0;
                                            student[j].taken_credits -= course[i].courseCredit;
                                            student[j].number_of_taken_courses--;
                                        }
                                    }
                                    for (k = 0; k < course[i].number_of_taked_students; k++)
                                    {
                                        if (0 == strcmp(&course[i].who_is_taked[k][0], word2))
                                        {
                                            course[i].who_is_taked[k][0] = 0;
                                            course[i].number_of_taked_students--;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else if (1 != ((student_valid && course_valid) && (is_student_member_of_course != 0)))
                {
                    if (student_valid != 1)
                        fprintf(foutput, "The specified student was not found.\n");
                    if (course_valid)
                        fprintf(foutput, "The specified course was not found.\n");
                    if (is_student_member_of_course != 1)
                        fprintf(foutput, "The student is not enrolled in the specified course.\n");
                }
                fprintf(foutput, "\n");
            }
        }
        else if (sscanf(readed, "%s %s", word1, word2) == 2)
        {
            if (0 == strcmp("LIST4", word1))
            {
                for (i = 0; i < number_of_students; i++)
                {
                    if (0 == strcmp(student[i].studentNumber, word2))
                    {
                        student_valid = 1;                                               
                        break;
                    }
                }

                for (j = 0; j <= student[i].number_of_taken_courses; j++)
                {
                    for (k = 0; k < number_of_courses; k++)
                    {
                        if (0 == strcmp(&student[i].taken_courses[j][0], course[k].courseCode))
                        {
                            is_student_member_of_course = 1;
                            break;
                        }
                    }
                }

                fprintf(foutput, "%s %s \n%s", "Command: ", readed, "Result: \n");

                if (student_valid && is_student_member_of_course)
                {
                    fprintf(foutput, "Student : %s - %s %s\n", student[i].studentNumber, student[i].studentName, student[i].studentSurname);
                    fprintf(foutput, "Participating Courses : %d\n", student[i].number_of_taken_courses);
                    for (k = 0; k <= student[i].number_of_taken_courses; k++)
                    {
                        for (j = 0; j < number_of_courses; j++)
                        {
                            if (0 == strcmp(&student[i].taken_courses[k][0], course[j].courseCode))
                            {
                                fprintf(foutput, "%s %s %d\n", course[j].courseCode, course[j].courseName, course[j].courseCredit);
                            }
                        }
                    }
                    fprintf(foutput, "Achieved Credits: %d\n", student[i].taken_credits);
                }
                else if ((student_valid && is_student_member_of_course) != 1)
                {
                    fprintf(foutput, "Empty!\n");
                }

                fprintf(foutput, "\n");
            }
            else if (0 == strcmp("LIST5", word1))
            {
                for (i = 0; i < number_of_lecturers; i++)
                {
                    if (0 == strcmp(lecturer[i].regNumber, word2))
                    {
                        lecturer_valid = 1;
                        if (lecturer[i].number_of_courses_taught > 0)
                        {
                            lecturer_course_load = 1;
                        }
                        break;
                    }
                }

                fprintf(foutput, "%s %s \n%s", "Command: ", readed, "Result: \n");

                if (lecturer_course_load && lecturer_valid)
                {
                    fprintf(foutput, "Lecturer : %s - %s %s\n", lecturer[i].regNumber, lecturer[i].regName, lecturer[i].regSurname);
                    fprintf(foutput, "The number of courses taught: %d\n", lecturer[i].number_of_courses_taught);
                    for (j = 0; j < lecturer[i].number_of_courses_taught; j++)
                    {
                        if (0 == strcmp(course[j].who_is_taught, lecturer[i].regNumber))
                        {
                            fprintf(foutput, "%s %s %d\n", course[j].courseCode, course[j].courseName, course[j].courseCredit);
                        }
                    }
                }
                else
                {
                    fprintf(foutput, "Empty!\n");
                }

                fprintf(foutput, "\n");
            }
            else if (0 == strcmp("LIST6", word1))
            {
                for (i = 0; i < number_of_courses; i++)
                {
                    if (0 == strcmp(course[i].courseCode, word2))
                    {
                        course_valid = 1;
                        if (course[i].number_of_taked_students > 0)
                        {
                            student_valid = 1;
                        }
                        if (course[i].is_teaching == 1)
                        {
                            who_is_taught = 1;
                        }
                        break;
                    }
                }

                fprintf(foutput, "%s %s \n%s", "Command: ", readed, "Result: \n");

                if (course_valid && student_valid && who_is_taught)
                {
                    fprintf(foutput, "Course : %s - %s %d\n", course[i].courseCode, course[i].courseName, course[i].courseCredit);

                    for (j = 0; j < number_of_lecturers; j++)
                    {
                        if (0 == strcmp(course[i].who_is_taught, lecturer[j].regNumber))
                        {
                            break;
                        }
                    }
                    fprintf(foutput, "Lecturer : %s - %s %s\n", lecturer[j].regNumber, lecturer[j].regName, lecturer[j].regSurname);
                    fprintf(foutput, "The number of participated students: %d\n", course[i].number_of_taked_students);

                    for (j = 0; j < number_of_students; j++)
                    {
                        if (0 == strcmp(&course[i].who_is_taked[j][0], student[j].studentNumber))
                        {
                            fprintf(foutput, "%s %s %s\n", student[j].studentNumber, student[j].studentName, student[j].studentSurname);
                        }
                    }
                }
                else
                {
                    fprintf(foutput, "Empty!\n");
                }

                fprintf(foutput, "\n");
            }
            else if (0 == strcmp("LIST7", word1))
            {
                if (number_of_students != 0)
                {
                    student_valid = 1;
                }
                for (i = 0; i < number_of_students; i++)
                {
                    if (student[i].taken_credits < atoi(word2))
                    {
                        any_student_with_this_credit = 1;
                    }
                }

                fprintf(foutput, "%s %s \n%s", "Command: ", readed, "Result: \n");

                if (any_student_with_this_credit && student_valid)
                {
                    for (i = 0; i < number_of_students; i++)
                    {
                        if (student[i].taken_credits < atoi(word2))
                        {
                            fprintf(foutput, "Student : %s - %s %s\n", student[i].studentNumber, student[i].studentName, student[i].studentSurname);
                        }
                    }
                }
                else
                {
                    fprintf(foutput, "Empty!\n");
                }

                fprintf(foutput, "\n");
            }
        }
        else if (sscanf(readed, "%s", word1) == 1)
        {
            if (0 == strcmp("LIST1", word1))
            {
                fprintf(foutput, "%s %s \n%s", "Command: ", readed, "Result: \n");          

                if (number_of_students > 0)
                {
                    for (i = 0; i < number_of_students; i++)
                    {
                        fprintf(foutput, "%s %s %s", student[i].studentNumber, student[i].studentName, student[i].studentSurname);
                        fprintf(foutput, "\n");
                    }
                }
                else if (number_of_students <= 0)
                    fprintf(foutput, "Empty!\n");

                fprintf(foutput, "\n");
            }
            else if (0 == strcmp("LIST2", word1))                                            
            {
                fprintf(foutput, "%s %s \n%s", "Command: ", readed, "Result: \n");
                if (number_of_lecturers > 0)
                {
                    for (i = 0; i < number_of_lecturers; i++)
                    {
                        fprintf(foutput, "%s %s %s", lecturer[i].regNumber, lecturer[i].regName, lecturer[i].regSurname);
                        fprintf(foutput, "\n");
                    }
                }
                else if (number_of_lecturers <= 0)
                    fprintf(foutput, "Empty!\n");

                fprintf(foutput, "\n");
            }
            else if (0 == strcmp("LIST3", word1))
            {
                fprintf(foutput, "%s %s \n%s", "Command: ", readed, "Result: \n");           
                if (number_of_courses > 0)
                {
                    for (i = 0; i < number_of_courses; i++)
                    {
                        fprintf(foutput, "%s %s %d", course[i].courseCode, course[i].courseName, course[i].courseCredit);
                        fprintf(foutput, "\n");
                    }
                }
                else if (number_of_courses <= 0)
                    fprintf(foutput, "Empty!\n");

                fprintf(foutput, "\n");
            }
        }
        else
        {
            printf("There was a problem reading commands!\n");
        }
    }
    fclose(fcommands);
    fclose(fstudent);
    fclose(fcourses);
    fclose(flecturers);
    fclose(foutput);

    free(student);
    free(course);
    free(lecturer);

    return 0;
    //DBMS
}