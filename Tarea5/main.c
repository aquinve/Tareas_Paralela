
#include <stdlib.h>
#include <stdio.h>
#include "xlsxio_write.h"

const char* filename = "prueba.xlsx";

//open .xlsx file for writing (will overwrite if it already exists)
int main(){
xlsxiowriter handle;
if ((handle = xlsxiowrite_open(filename, "MySheet")) == NULL) {
  fprintf(stderr, "Error creating .xlsx file\n");
  return 1;
}

//write column names
xlsxiowrite_add_column(handle, "aasd", 16);
xlsxiowrite_add_column(handle, "alooo", 0);
xlsxiowrite_next_row(handle);

//write data
int i;
for (i = 0; i < 1000; i++) {
  xlsxiowrite_add_cell_string(handle, "Test");
  xlsxiowrite_add_cell_int(handle, i);
  xlsxiowrite_next_row(handle);
}

//close .xlsx file
xlsxiowrite_close(handle);
}
