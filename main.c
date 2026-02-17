#define _CRT_SECURE_NO_WARNINGS
#define SIZE 1000
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

void log_msg(char* message) {
	time_t tCurT = time(NULL);
	char* sCurT = ctime(&tCurT);
	sCurT[strlen(sCurT) - 1] = '\0';
	FILE* log = fopen("log.txt", "a");
	if (log == NULL) return;
	fprintf(log, "[%s] %s\n", sCurT, message);
	fclose(log);
}
int main(void) {
	//open input file
	log_msg("Program started");
	char sNameOfInputFile[SIZE];
	printf("Enter the input file name: ");
	scanf("%s", sNameOfInputFile);
	FILE* fInputFile = fopen(sNameOfInputFile, "rb");
	if (fInputFile == NULL) { log_msg("file not found");log_msg("Program ended"); return 1; }
	else log_msg("File has been opened");
	//int args
	double x, y,u,Q;
	fread(&x, sizeof(double), 1, fInputFile);
	fread(&y, sizeof(double), 1, fInputFile);
	fread(&u, sizeof(double), 1, fInputFile);
	char msg[SIZE];
	printf("x=%lf,y=%lf,u=%lf\n", x, y, u);
	sprintf(msg, "x=%lf,y=%lf,u=%lf", x, y, u);
	log_msg(msg);
	Q = pow(u, (x + y) / 2) - cbrt((x - 1) / (fabs(y) + 1));
	printf("Q=%lf\n", Q);
	sprintf(msg, "Q=%lf", Q);
	log_msg(msg);
	fclose(fInputFile);
	log_msg("Input file has been closed");
	//output file
	printf("Enter type of file:\n");
	printf("1 - binary file\n");
	printf("2 - text file\n");
	int nTypeOfFile;
	scanf("%d", &nTypeOfFile);
	switch (nTypeOfFile){
	case 1: {
			printf("Enter the output file name: ");
			char sNameOfOutputFile[SIZE];
			scanf("%s", sNameOfOutputFile);
			FILE* fOutputFile = fopen(sNameOfOutputFile, "wb");
			if (fOutputFile == NULL) { log_msg("output file not created");log_msg("Program ended"); return 1; }
			else log_msg("Output file has been opened");
			fwrite(&Q, sizeof(double), 1, fOutputFile);
			log_msg("Result has been written to output file");
			fclose(fOutputFile);
			log_msg("Output file has been closed");
			log_msg("Program ended");
			break;
	}
	case 2:
		{
			printf("Enter the output file name: ");
			char sNameOfOutputFile[SIZE];
			scanf("%s", sNameOfOutputFile);
			FILE* fOutputFile = fopen(sNameOfOutputFile, "w");
			if (fOutputFile == NULL) { log_msg("output file not created");log_msg("Program ended"); return 1; }
			else log_msg("Output file has been opened");
			fprintf(fOutputFile, "Q=%lf", Q);
			log_msg("Result has been written to output file");
			fclose(fOutputFile);
			log_msg("Output file has been closed");
			log_msg("Program ended");
			break;
	}
		default :
		{
			log_msg("invalid file type");
			log_msg("Program ended");
			printf("Invalid file type\n");
			return 1;
		}
	}
	return 0;
}