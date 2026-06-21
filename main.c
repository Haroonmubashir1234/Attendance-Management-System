#include<stdio.h>
#include<string.h>

#define MAX 50
#define DAYS 30
#define SUBJECTS 3

//STRUCTURES//

struct Student
{
    int id;
    char name[50];
    char password[30];
};

struct Teacher
{
    char username[30];
    char password[30];
};

struct ExamDept
{
    char username[30];
    char password[30];
};

//VARIABLES//

struct Student students[MAX];
struct Teacher teachers[MAX];
struct ExamDept examAdmins[MAX];

int studentCount=0;
int teacherCount=0;
int examCount=0;

int attendance[MAX][SUBJECTS][DAYS];


//SEARCH FUNCTION//

int searchByID(int id)
{
    int i;

    for(i=0;i<studentCount;i++)
    {
        if(students[i].id==id)
        return i;
    }

    return -1;
}

//ATTENDANCE CALCULATION//

float calculateAttendance(int index)
{
    int *ptr;

    int present=0;

    int total=
    SUBJECTS*DAYS;

    int s,d;

    ptr=&attendance[index][0][0];

    for(s=0;s<SUBJECTS;s++)
    {
        for(d=0;d<DAYS;d++)
        {
            if(*(ptr+
            s*DAYS+d)==1)
            {
                present++;
            }
        }
    }

    return
    ((float)present/total)*100;
}

FILE *fp;

//FILE HANDLING//

void loadStudents()
{
    fp=fopen("students.txt","r");

    if(fp==NULL)
        return;

    while(fscanf(fp,"%d %s %s",
    &students[studentCount].id,
    students[studentCount].name,
    students[studentCount].password)!=EOF)
    {
        studentCount++;
    }

    fclose(fp);
}


void loadTeachers()
{
    fp=fopen("teachers.txt","r");

    if(fp==NULL)
        return;

    while(fscanf(fp,"%s %s",
    teachers[teacherCount].username,
    teachers[teacherCount].password)!=EOF)
    {
        teacherCount++;
    }

    fclose(fp);
}


void loadExam()
{
    fp=fopen("exam.txt","r");

    if(fp==NULL)
        return;

    while(fscanf(fp,"%s %s",
    examAdmins[examCount].username,
    examAdmins[examCount].password)!=EOF)
    {
        examCount++;
    }

    fclose(fp);
}

void loadAttendance()
{
    fp=fopen("attendance.dat","rb");

    if(fp==NULL)
        return;

    fread(attendance,
    sizeof(attendance),
    1,
    fp);

    fclose(fp);
}

void saveAttendance()
{
    fp = fopen("attendance.dat","wb");

    fwrite(attendance,sizeof(attendance),1,fp);

    fclose(fp);
}

void saveAttendanceText()
{
    FILE *fp;
    int s, sub, day;

    fp = fopen("attendance.txt","w");

    if(fp == NULL)
        return;

    for(s=0; s<studentCount; s++)
    {
        fprintf(fp,"\nStudent ID: %d\nName: %s\n",
        students[s].id,
        students[s].name);

        for(sub=0; sub<SUBJECTS; sub++)
        {
            fprintf(fp,"Subject %d: ", sub+1);

            for(day=0; day<DAYS; day++)
            {
                fprintf(fp,"%d ",
                attendance[s][sub][day]);
            }

            fprintf(fp,"\n");
        }

        fprintf(fp,"\n----------------------\n");
    }

    fclose(fp);
}

void openFile(char filename[])
{
    FILE *fp;
    char ch;

    fp = fopen(filename,"r");

    if(fp == NULL)
    {
        printf("\nCannot open file: %s", filename);
        return;
    }

    printf("\n\n===== %s =====\n", filename);

    while((ch = fgetc(fp)) != EOF)
    {
        printf("%c", ch);
    }

    fclose(fp);
}

//STUDENT SIGNUP//

void studentSignup()
{
    printf("\nStudent ID: ");
    scanf("%d",&students[studentCount].id);

    printf("Name: ");
    scanf("%s",students[studentCount].name);

    printf("Password: ");
    scanf("%s",students[studentCount].password);

    fp=fopen("students.txt","a");

    fprintf(fp,"%d %s %s\n",
    students[studentCount].id,
    students[studentCount].name,
    students[studentCount].password);

    fclose(fp);

    studentCount++;

    printf("\nSignup Successful\n");
}

//STUDENT LOGIN//

int studentLogin()
{
    int id;
    char pass[30];
    int i;

    printf("\nEnter ID: ");
    scanf("%d",&id);

    printf("Password: ");
    scanf("%s",pass);

    for(i=0;i<studentCount;i++)
    {
        if(students[i].id==id &&
        strcmp(students[i].password,pass)==0)
        {
            return i;
        }
    }

    return -1;
}

//TEACHER SIGNUP//

void teacherSignup()
{
    printf("\nUsername: ");
    scanf("%s",teachers[teacherCount].username);

    printf("Password: ");
    scanf("%s",teachers[teacherCount].password);

    fp=fopen("teachers.txt","a");

    fprintf(fp,"%s %s\n",
    teachers[teacherCount].username,
    teachers[teacherCount].password);

    fclose(fp);

    teacherCount++;

    printf("\nTeacher Signup Successful\n");
}


//TEACHER LOGIN//

int teacherLogin()
{
    char user[30];
    char pass[30];

    int i;

    printf("\nUsername: ");
    scanf("%s",user);

    printf("Password: ");
    scanf("%s",pass);

    for(i=0;i<teacherCount;i++)
    {
        if(strcmp(user,
        teachers[i].username)==0 &&
        strcmp(pass,
        teachers[i].password)==0)
        {
            return 1;
        }
    }

    return 0;
}


//EXAMINATION SIGNUP//

void examSignup()
{
    printf("\nUsername: ");
    scanf("%s",
    examAdmins[examCount].username);

    printf("Password: ");
    scanf("%s",
    examAdmins[examCount].password);

    fp=fopen("exam.txt","a");

    fprintf(fp,"%s %s\n",
    examAdmins[examCount].username,
    examAdmins[examCount].password);

    fclose(fp);

    examCount++;

    printf("\nExam Department Signup Successful\n");
}


//EXAMINATION LOGIN//

int examLogin()
{
    char user[30];
    char pass[30];

    int i;

    printf("\nUsername: ");
    scanf("%s",user);

    printf("Password: ");
    scanf("%s",pass);

    for(i=0;i<examCount;i++)
    {
        if(strcmp(user,
        examAdmins[i].username)==0
        &&
        strcmp(pass,
        examAdmins[i].password)==0)
        {
            return 1;
        }
    }

    return 0;
}

//ADD STUDENT//

void addStudent()
{
    studentSignup();
}

//VIEW ATTENDANCE//

void viewAttendance()
{
    int id;
    int index;

    int subject,day;

    printf("\nStudent ID: ");
    scanf("%d",&id);

    index=searchByID(id);

    if(index==-1)
    {
        printf("\nStudent Not Found");
        return;
    }

    printf("\nName : %s",
    students[index].name);

    for(subject=0;subject<SUBJECTS;subject++)
    {
        printf("\n\nSubject %d:\n",
        subject+1);

        for(day=0;day<DAYS;day++)
        {
            printf("%d ",
            attendance[index][subject][day]);
        }
    }

}

//MARK ATTENDANCE//

void markAttendance()
{
    int id;
    int index;

    int subject;
    int day;

    printf("\nEnter Student ID: ");
    scanf("%d",&id);

    index=searchByID(id);

    if(index==-1)
    {
        printf("\nStudent Not Found");
        return;
    }

    printf("\nSubject (0-2): ");
    scanf("%d",&subject);

    printf("Day (1-30): ");
    scanf("%d",&day);

    printf("1=Present 0=Absent : ");
    scanf("%d",
    &attendance[index][subject][day-1]);
    
    saveAttendance();
    printf("\nAttendance Saved");
    saveAttendanceText();
}

//UPDATE ATTENDANCE//

void updateAttendance()
{
    int id;
    int index;

    int subject;
    int day;

    printf("\nStudent ID: ");
    scanf("%d",&id);

    index=searchByID(id);

    if(index==-1)
    {
        printf("\nStudent Not Found");
        return;
    }

    printf("Subject: ");
    scanf("%d",&subject);

    printf("Day: ");
    scanf("%d",&day);

    printf("New Value (1/0): ");
    scanf("%d",
    &attendance[index][subject][day-1]);
    
    saveAttendance();
    saveAttendanceText();
    printf("\nUpdated Successfully");
}


//DELETE ATTENDANCE//

void deleteAttendance()
{
    int id;
    int index;

    int subject;
    int day;

    printf("\nStudent ID: ");
    scanf("%d",&id);

    index=searchByID(id);

    if(index==-1)
    {
        printf("\nStudent Not Found");
        return;
    }

    printf("Subject: ");
    scanf("%d",&subject);

    printf("Day: ");
    scanf("%d",&day);

    attendance[index][subject][day-1]=0;
    
    saveAttendance();
    saveAttendanceText();
    printf("\nDeleted");
}


//SEARCH STUDENT//

void searchStudent()
{
    int id;
    int index;

    printf("\nEnter Student ID: ");
    scanf("%d",&id);

    index=searchByID(id);

    if(index==-1)
    {
        printf("\nStudent Not Found");
    }

    else
    {
        printf("\nStudent Found");

        printf("\nID : %d",
        students[index].id);

        printf("\nName : %s",
        students[index].name);
    }
}

//TEACHER DASHBOARD//

void teacherPanel()
{
    int choice;

    do
    {
        printf("\n\n------Teacher Panel------");

        printf("\n1.Add Student");
        printf("\n2.Mark Attendance");
        printf("\n3.View Attendance");
        printf("\n4.Update Attendance");
        printf("\n5.Delete Attendance");
        printf("\n6.Search Student");
        printf("\n7.View Students File");
        printf("\n8.View Teachers File");
        printf("\n9.View Attendance File");
        printf("\n10.Logout");

        printf("\nChoice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:

            addStudent();
            break;

            case 2:

            markAttendance();
            break;

            case 3:

            viewAttendance();
            break;

            case 4:

            updateAttendance();
            break;

            case 5:

            deleteAttendance();
            break;

            case 6:

            searchStudent();
            break;
            
            case 7:
            openFile("students.txt");
            break;
            
            case 8:
            openFile("teachers.txt");
            break;

            case 9:
            openFile("attendance.txt");
            break;
        }

    }while(choice!=10);

}

//STUDENT DASHBOARD//

void studentPanel(int index)
{
    int choice;

    do
    {
        printf("\n-----Student Panel-----");

        printf("\n1.View Attendance");
        printf("\n2.View Attendance %%");
        printf("\n3.Logout");

        printf("\nChoice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:

            viewAttendance();
            break;

            case 2:

            printf("\nAttendance = %.2f %%"
            ,calculateAttendance(index));

            break;
        }

    }while(choice!=3);

}

//STUDENT MENU//

void studentMenu()
{
    int choice;
    int index;

    do
    {
        printf("\n1.Signup");
        printf("\n2.Login");
        printf("\n3.Back");

        printf("\nChoice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:

            studentSignup();
            break;

            case 2:

            index=studentLogin();

            if(index!=-1)
            {
                printf("\nLogin Successful");
                studentPanel(index);
            }
            else
            {
                printf("\nWrong Login");
            }

            break;
        }

    }while(choice!=3);
}

//TEACHER MENU//

void teacherMenu()
{
    int choice;

    do
    {
        printf("\n1.Signup");
        printf("\n2.Login");
        printf("\n3.Back");

        printf("\nChoice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:

            teacherSignup();
            break;

            case 2:

            if(teacherLogin())
            {
                printf("\nLogin Successful");
                teacherPanel();
            }

            else
            {
                printf("\nWrong Login");
            }

            break;
        }

    }while(choice!=3);
}

//EXAMINATION DASHBOARD//

void examPanel()
{
    int choice;
    int id;
    int index;
    float percent;

    do
    {
        printf("\n\n----- Exam Panel -----");

        printf("\n1.Check Eligibility");
        printf("\n2.View Students File");
        printf("\n3.View Attendance File");
        printf("\n4.View Teachers File");
        printf("\n5.View Exam File");
        printf("\n6.Logout");

        printf("\nChoice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:

                printf("\nEnter Student ID: ");
                scanf("%d",&id);

                index = searchByID(id);

                if(index == -1)
                {
                    printf("\nStudent Not Found");
                }
                else
                {
                    percent = calculateAttendance(index);

                    printf("\nAttendance: %.2f%%", percent);

                    if(percent >= 75)
                        printf("\nEligible For Exam");
                    else
                        printf("\nNot Eligible");
                }

                break;

            case 2:
                openFile("students.txt");
                break;

            case 3:
                openFile("attendance.txt");
                break;
            
            case 4:
                openFile("teachers.txt");
                break;
            
            case 5:
                openFile("exam.txt");
                break;
        }

    }while(choice != 6);
}

//EXAM MENU//

void examMenu()
{
    int choice;

    do
    {
        printf("\n----- Exam Department -----");

        printf("\n1.Signup");
        printf("\n2.Login");
        printf("\n3.Back");

        printf("\nChoice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                examSignup();
                break;

            case 2:
                if(examLogin())
                {
                    printf("\nLogin Successful");
                    examPanel();
                }
                else
                {
                    printf("\nWrong Login");
                }
                break;
        }

    }while(choice != 3);
}

//MAIN MENU//

void mainMenu()
{
    int choice;
    int index;

    do
    {
        printf("\n\n====== ATTENDANCE MANAGEMENT SYSTEM ======");

        printf("\n1.Student");
        printf("\n2.Teacher");
        printf("\n3.Exam Department");
        printf("\n4.Exit");

        printf("\nChoice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:

            studentMenu();
            break;

            case 2:

            teacherMenu();
            break;

            case 3:

            examMenu();
            break;

            case 4:

            printf("\nProgram Ended");
            break;

            default:

            printf("\nInvalid Choice");
        }

    }while(choice!=4);

}

//MAIN FUNCTION//

int main()
{
    loadStudents();

    loadTeachers();

    loadExam();

    loadAttendance();

    mainMenu();

    return 0;
}
