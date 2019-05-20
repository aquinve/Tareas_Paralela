#include <xlsxio_read.h>
#include <stdlib.h>
#include <stdio.h>

const char* filename = "example.xlsx";


int main(){
//open .xlsx file for reading
xlsxioreader xlsxioread;
if ((xlsxioread = xlsxioread_open(filename)) == NULL) {
  fprintf(stderr, "Error opening .xlsx file\n");
  return 1;
}

//read values from first sheet
char* value;
xlsxioreadersheet sheet;
const char* sheetname = NULL;
printf("Contents of first sheet:\n");
if ((sheet = xlsxioread_sheet_open(xlsxioread, sheetname, XLSXIOREAD_SKIP_EMPTY_ROWS)) != NULL) {
  //read all rows
  while (xlsxioread_sheet_next_row(sheet)) {
    //read all columns
    while ((value = xlsxioread_sheet_next_cell(sheet)) != NULL) {
      printf("%s\t", value);
      free(value);
    }
    printf("\n");
  }
  xlsxioread_sheet_close(sheet);
}

//clean up
xlsxioread_close(xlsxioread);
}