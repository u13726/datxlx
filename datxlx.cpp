// datxlx.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "xlsxwriter.h"

int main(int argc, char *argv[]) 
{

	FILE *R;
	lxw_workbook  *workbook = workbook_new("datbbo.xlsx");
	lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);
	int row = 0;
	int col = 0;

	if (argc>1 && (0==fopen_s(&R,argv[1],"r")))
	{
		unsigned char line[4096];
		while (fgets((char *)line, sizeof line, R))
		{
			col=0;
			if (strlen((char *)line)>0 && line[strlen((char *)line)-1] == 0X0A) line[strlen((char *)line)-1] = 0;
			if (strlen((char *)line)>0 && line[strlen((char *)line)-1] == 0X0D) line[strlen((char *)line)-1] = 0;
			unsigned char *del;
			for (unsigned char *si = line; si && strlen((char *)si); col++)
			{
				if (del = (unsigned char *)strchr((char *)si, 0xB9))
				{
					*del = 0;
					if (strlen((char *)si))
					    worksheet_write_string(worksheet, row, col, (char *)si, NULL);
					*del = 0xB9;
					si = del + 1;
				}
				else
				{
					worksheet_write_string(worksheet, row, col, (char *)si, NULL);
					si = (unsigned char *)strchr((char *)si, 0);
				}
			}
			row++;
		} 
	}
    return workbook_close(workbook);
}

