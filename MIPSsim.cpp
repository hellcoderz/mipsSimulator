//“On my honor, I have neither given nor received unauthorized aid on this assignment”

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

#define MEM 256
#define AUTHOR "Vikrant Sagar"
#define COURSE "Computer Architecture"
#define PROJECT "Project 1"

//class to hold 32 bit data structure and functions operated on it
class instr32{
	public:
		bool bits[32];	//32 bit bool array to hold 32 bit number

		instr32(){
			for(int i=0;i<32;i++)
				bits[i] = 0;
		}

		//constructor to convert 32 char binary string to 32 bit bool array
		instr32(string str){
			int i = 0;
			for ( std::string::iterator it=str.begin(); it!=str.end(); ++it){
				if(*it == '1')
					bits[i] = 1;
				else
					bits[i] = 0;

				i++;
			}
		}
		
		//function to print the bool array as on the screen
		void print(){
			for(int i=0;i< 32;i++){
				cout << bits[i];
			}
			//cout << endl;
		}
		
		//operator overloading to assign 32 char string to 32 bit bool array 
		void operator=(string str){
			int i = 0;
			for ( std::string::iterator it=str.begin(); it!=str.end(); ++it){
				if(*it == '1')
					bits[i] = 1;
				else
					bits[i] = 0;

				i++;
			}

		}

		//function to convert instr32 data structure to long num
		instr32 num_2_twos_complement(long num){
			instr32 temp;
			if(num < 0){
				temp = num;
				temp = ~temp;
				temp = temp + instr32("00000000000000000000000000000001");
				return temp;

			}else{
				temp = num;
				return temp;
			}
		}
		
		//operator overloading to assign number to 32 bit bool array
		void operator=(long num){

			instr32 ins;

			copy(ins);
			int i = 31;

			for(int i=31;i>=0;i--){
				if(num){
					if(num % 2 == 1)
						bits[i] = 1;
					else
						bits[i] = 0;

					num = num / 2;
					//cout << "num = " << num << endl;
					
				}
			}
			/*
			for(int i=0;i< 32;i++){
				cout << bits[i] ;
			}
			cout << endl;
			*/

		}

		//function to copy instr32 data structure to current object
		void copy(instr32 ins){
			for(int i=0;i< 32;i++){
				bits[i] = ins.bits[i];
			}
		}

		//operator overloading to do logical AND on the two instr32 type objects
		instr32 operator&(instr32 right){
			instr32 ins;
			for(int i=0;i< 32;i++){
				ins.bits[i] = bits[i] & right.bits[i];
			}

			return ins;
		}

		//operator overloading to do logical XOR on the two instr32 type objects
		instr32 operator^(instr32 right){
			instr32 ins;
			for(int i=0;i< 32;i++){
				ins.bits[i] = bits[i] ^ right.bits[i];
			}

			return ins;
		}

		//operator overloading to do logical OR on the two instr32 type objects
		instr32 operator|(instr32 right){
			instr32 ins;
			for(int i=0;i< 32;i++){
				ins.bits[i] = bits[i] | right.bits[i];
			}

			return ins;
		}

		//operator overloading to do logical RIGHT SHIFT on instr32 type objects
		instr32 operator>>(int shift){
			instr32 ins;

			if(shift > 31)
				return ins;
			if(shift < 1){
				for(int i=0;i < 32;i++){
					ins.bits[i] = bits[i];
				}

				return ins;
			}

			for(int i=31-shift;i >=0 ;i--){
				ins.bits[i+shift] = bits[i];
			}

			return ins;
		}
		
		//operator overloading to do logical LEFT SHIFT on instr32 type objects
		instr32 operator<<(int shift){
			instr32 ins;

			if(shift > 31)
				return ins;
			if(shift < 1){
				for(int i=0;i < 32;i++){
					ins.bits[i] = bits[i];
				}

				return ins;
			}

			for(int i=shift;i < 32 ;i++){
				ins.bits[i-shift] = bits[i];
			}

			return ins;
		}
		
		//operator overloading to do arthmatic RIGHT SHIFT on instr32 type objects
		instr32 SRA(instr32 ins,long shift){
			bool flag = 0;
			instr32 temp;
			if(bits[0] == 1)
				flag = 1;
			temp = ins >> shift;
			if(flag)
				for(int i=0;i < shift ; i++)
					temp.bits[i] = 1;

			return temp; 
		}

		//function to convert current object to long number
		long toNum(){
			long num = 0;
			long mul = 1;
			for(int i=31;i>=0;i--){
				if(bits[i] == 1){
					num += mul;
				}

				mul *= 2;
			}

			return num;

		}

		//operator overloading to compare two instr32 object
		bool operator==(instr32 right){
			for(int i=0;i< 32;i++){
				if(bits[i] != right.bits[i])
					return 0;
			}

			return 1;
		}

		instr32 operator~(){
			instr32 ins;
			for(int i=0;i< 32;i++){
				ins.bits[i] = !bits[i];
			}
			return ins;
		}

		//function to add to bit
		bool add(bool a,bool b){

			if(a == b)
				return 0;
			else
				return 1;

		}

		//operator overloading to do bitwuse ADD operation on two instr32 type objects
		instr32 operator+(instr32 right){
			bool carry = 0,carry1,carry2;
			bool ans;
			instr32 ins;
			for(int i=31;i>=0;i--){
				//cout <<"initial carry = " << carry << endl;
				//cout << bits[i] << " + " << right.bits[i] << endl;
				ans = add(carry,right.bits[i]);
				carry1 = carry & right.bits[i];
				//cout << "ans = " << ans << "\tcarry = " << carry;
				ins.bits[i] = add(bits[i],ans);
				carry2 = bits[i] & ans;
				carry = carry1 | carry2 ;	
				//cout << "ins.bits[" << i <<"] = " << ins.bits[i] << endl;

			}
			return ins;

		}
};

//class to hold opcodes 
class OPCODES{
public:
		instr32 J,JR,BEQ,BLTZ,BGTZ,BREAK,SW,LW,SLL,SRL,SRA,NOP,ADD,SUB,MUL,AND,OR,XOR,NOR,SLT,ADDI,ANDI,ORI,XORI;

		OPCODES(){
			//category 1
			J 		=	"01000000000000000000000000000000";
			JR 		=	"01000100000000000000000000000000";
			BEQ		=	"01001000000000000000000000000000";
			BLTZ 	=	"01001100000000000000000000000000";
			BGTZ 	=	"01010000000000000000000000000000";
			BREAK 	=	"01010100000000000000000000000000";
			SW 		=	"01011000000000000000000000000000";
			LW 		=	"01011100000000000000000000000000";
			SLL 	=	"01100000000000000000000000000000";
			SRL 	=	"01100100000000000000000000000000";
			SRA		=	"01101000000000000000000000000000";
			NOP 	=	"01101100000000000000000000000000";

			//category 2
			ADD		=	"11000000000000000000000000000000";
			SUB		=	"11000100000000000000000000000000";
			MUL		=	"11001000000000000000000000000000";
			AND 	=	"11001100000000000000000000000000";
			OR	 	=	"11010000000000000000000000000000";
			XOR 	=	"11010100000000000000000000000000";
			NOR		=	"11011000000000000000000000000000";
			SLT		=	"11011100000000000000000000000000";
			ADDI 	=	"11100000000000000000000000000000";
			ANDI	=	"11100100000000000000000000000000";
			ORI		=	"11101000000000000000000000000000";
			XORI	=	"11101100000000000000000000000000";
		}
};


//class to hold each instruction data 
class instr_decoded{

public:
	instr32 ins;
	long rs,rd,rt,sa,base;
	long signed_offset;

	instr_decoded(){
		rs = rd = rt = sa = signed_offset = base = 0;
	}
};



//class to disassemble the input file
class Dissassembler{

	public:
		instr32 R[32];	//32 registers
		instr32 memory[MEM];	//total memory
		int data_offset;
		int instr_offset;
		int code_size;
		OPCODES opCodes;
		ofstream out,out2;
		vector<instr_decoded*> instr;
		map<int,string> m2c;
		string FILE_NAME;


	Dissassembler(){
		data_offset = 0;
		code_size = 0;
		instr_offset = 256;
		for(int i;i<32;i++){
			R[i] = 0;
		}

		out.open("generated_disassembly.txt");
		out2.open("generated_simulate.txt");

	}

	void print_instr32(instr32 mem){
			for(int i=0;i< 32;i++){
				out << mem.bits[i];
			}
			//cout << endl;
		}
	//read data from file and store it in memory
	void file2memory(char* file){
		FILE_NAME = file;
		string line;
  		ifstream myfile;
  		myfile.open(file);
  		int i = 0;
    	while ( myfile.good() ){

      		getline (myfile,line);
      		if(line.length() != 32)
      			break;
      		memory[i++] = line;
    	}
    	myfile.close();
  		code_size = i;
	}

	//find where data segment starts
	void getDataOffset(){
		instr32 mask;
		mask = "11111100000000000000000000000000";
		int i = 0;
		for(i=0;i<MEM;i++){
			if((memory[i] & mask) == opCodes.BREAK)
				break;

		}
		data_offset = (i+1)*4 + 252 + 4;
	}

	//to extract rs value fron instr32 object
	long rs(instr32 ins){
		instr32 temp;
		temp.copy(ins);
		instr32 maskrs("00000011111000000000000000000000");

		temp = temp & maskrs;
		temp = temp >> 21;
		return temp.toNum(); 
	}
	
	//to extract rt value fron instr32 object
	long rt(instr32 ins){
		instr32 temp;
		temp.copy(ins);
		instr32 maskrt("00000000000111110000000000000000");

		temp = temp & maskrt;
		temp = temp >> 16;
		return temp.toNum(); 
	}

	//to extract rd value fron instr32 object
	long rd(instr32 ins){
		instr32 temp;
		temp.copy(ins);
		instr32 maskrt("00000000000000001111100000000000");

		temp = temp & maskrt;
		temp = temp >> 11;
		return temp.toNum(); 
	}

	//to extract sa value fron instr32 object
	long sa(instr32 ins){
		instr32 temp;
		temp.copy(ins);
		instr32 maskrt("00000000000000000000011111000000");

		temp = temp & maskrt;
		temp = temp >> 6;
		return temp.toNum(); 
	}

	//function to disaasemble the machine code to assembly codes
	void disassemble_instructions(){
		getDataOffset();
		int END_OF_INSTR = (data_offset-256)/4;
		instr32 mask;
		instr32 op, temp, tempPC;
		
		long PC = 256;

		mask = "11111100000000000000000000000000";

		//cout << "Data Offset = " << data_offset << endl;
		//cout << "END_OF_INSTR = " << END_OF_INSTR <<  endl;
		
		
		//loop to iterate over all instructions
		for(int i=0;i< END_OF_INSTR;i++){
			PC = 256 + i*4;
			op = memory[i] & mask;

			if(op == opCodes.J){
				instr32 mask4("11110000000000000000000000000000");
				instr32 mask26("00000011111111111111111111111111");

				temp = memory[i] & mask26;
				temp = temp << 2;
				//cout << (long)PC + 4 << endl;;
				tempPC = (long)PC + 4;
				tempPC = tempPC & mask4;
				temp = temp | tempPC;
				print_instr32(memory[i]);
				out << "\t" << PC << "\t" ;
				out << "J #" << temp.toNum() << endl;

			}else if(op == opCodes.JR){
				instr32 maskrs("00000011111000000000000000000000");

				temp = memory[i] & maskrs;
				temp = temp >> 21;
				print_instr32(memory[i]);
				out << "\t" << PC << "\t" ;
				out << 'JR R' << temp.toNum() << endl;

			}else if(op == opCodes.BEQ){
				instr32 mask16("00000000000000001111111111111111");
				long offset;
				long rs_val,rt_val;
				rs_val = rs(memory[i]);
				rt_val = rt(memory[i]);

				temp = memory[i] & mask16;
				temp = temp << 2;
				//out << (long)PC + 4 << endl;;
				tempPC = (long)PC + 4;
				if(temp.bits[16] == 1){
					temp = ~ temp;
					instr32 mask18("00000000000000111111111111111111");
					temp = temp & mask18;
					temp = temp + instr32("00000000000000000000000000000001");
					offset = -temp.toNum();
				}else{
					offset = temp.toNum();

				}
				print_instr32(memory[i]);
				out << "\t" << PC << "\t" ;
				out << "BEQ R" << rs_val <<", R" << rt_val <<", #" << offset << endl;

			}else if(op == opCodes.BLTZ){
				instr32 mask16("00000000000000001111111111111111");
				long offset;
				long rs_val;
				rs_val = rs(memory[i]);

				temp = memory[i] & mask16;
				temp = temp << 2;
				//out << (long)PC + 4 << endl;;
				tempPC = (long)PC + 4;
				if(temp.bits[16] == 1){
					temp = ~ temp;
					instr32 mask18("00000000000000111111111111111111");
					temp = temp & mask18;
					temp = temp + instr32("00000000000000000000000000000001");
					offset = -temp.toNum();
				}else{
					offset = temp.toNum();

				}
				print_instr32(memory[i]);
				out << "\t" << PC << "\t" ;
				out << "BLTZ R" << rs_val <<", #" << offset << endl;

			}else if(op == opCodes.BGTZ){
				instr32 mask16("00000000000000001111111111111111");
				long offset;
				long rs_val;
				rs_val = rs(memory[i]);

				temp = memory[i] & mask16;
				temp = temp << 2;
				//out << (long)PC + 4 << endl;;
				tempPC = (long)PC + 4;
				if(temp.bits[16] == 1){
					temp = ~ temp;
					instr32 mask18("00000000000000111111111111111111");
					temp = temp & mask18;
					temp = temp + instr32("00000000000000000000000000000001");
					offset = -temp.toNum();
				}else{
					offset = temp.toNum();

				}
				print_instr32(memory[i]);
				out << "\t" << PC << "\t" ;
				out << "BGTZ R" << rs_val <<", #" << offset << endl;

			}else if(op == opCodes.BREAK){
				print_instr32(memory[i]);
				out << "\t" << PC << "\t" ;
				out << "BREAK" << endl;
				break;

			}else if(op == opCodes.SW){
				instr32 mask16("00000000000000001111111111111111");
				long offset;
				long rs_val,rt_val;
				rs_val = rs(memory[i]);
				rt_val = rt(memory[i]);

				temp = memory[i] & mask16;
				if(temp.bits[18] == 1){
					temp = ~ temp;
					temp = temp & mask16;
					temp = temp + instr32("00000000000000000000000000000001");
					offset = -temp.toNum();
				}else{
					offset = temp.toNum();

				}

				print_instr32(memory[i]);
				out << "\t" << PC << "\t" ;
				out << "SW R" << rt_val <<", " << offset << "(R" << rs_val << ")" << endl;

			}else if(op == opCodes.LW){
				instr32 mask16("00000000000000001111111111111111");
				long offset;
				long rs_val,rt_val;
				rs_val = rs(memory[i]);
				rt_val = rt(memory[i]);

				temp = memory[i] & mask16;
				if(temp.bits[18] == 1){
					temp = ~ temp;
					temp = temp & mask16;
					temp = temp + instr32("00000000000000000000000000000001");
					offset = -temp.toNum();
				}else{
					offset = temp.toNum();

				}

				print_instr32(memory[i]);
				out << "\t" << PC << "\t" ;
				out << "LW R" << rt_val <<", " << offset << "(R" << rs_val << ")" << endl;

			}else if(op == opCodes.SLL){
				instr32 mask16("00000000000000001111111111111111");
				long offset;
				long rd_val,rt_val,sa_val;
				rd_val = rd(memory[i]);
				rt_val = rt(memory[i]);
				sa_val = sa(memory[i]);

				print_instr32(memory[i]);
				out << "\t" << PC << "\t" ;
				out << "SLL R" << rd_val <<", R" << rt_val << ", #" << sa_val << endl;

			}else if(op == opCodes.SRL){
				instr32 mask16("00000000000000001111111111111111");
				long offset;
				long rd_val,rt_val,sa_val;
				rd_val = rd(memory[i]);
				rt_val = rt(memory[i]);
				sa_val = sa(memory[i]);

				print_instr32(memory[i]);
				out << "\t" << PC << "\t" ;
				out << "SRL R" << rd_val <<", R" << rt_val << ", #" << sa_val << endl;

			}else if(op == opCodes.SRA){
				instr32 mask16("00000000000000001111111111111111");
				long offset;
				long rd_val,rt_val,sa_val;
				rd_val = rd(memory[i]);
				rt_val = rt(memory[i]);
				sa_val = sa(memory[i]);

				print_instr32(memory[i]);
				out << "\t" << PC << "\t" ;
				out << "SRA R" << rd_val <<", R" << rt_val << ", #" << sa_val << endl;

			}else if(op == opCodes.NOP){
				print_instr32(memory[i]);
				out << "\t" << PC << "\t" ;
				out << "NOP" << endl;

			}else if(op == opCodes.ADD){
				long rd_val,rt_val,rs_val;
				rd_val = rd(memory[i]);
				rt_val = rt(memory[i]);
				rs_val = rs(memory[i]);

				print_instr32(memory[i]);
				out << "\t" << PC << "\t" ;
				out << "ADD R" << rd_val <<", R" << rs_val << ", R" << rt_val << endl;

			}else if(op == opCodes.SUB){
				long rd_val,rt_val,rs_val;
				rd_val = rd(memory[i]);
				rt_val = rt(memory[i]);
				rs_val = rs(memory[i]);

				print_instr32(memory[i]);
				out << "\t" << PC << "\t" ;
				out << "SUB R" << rd_val <<", R" << rs_val << ", R" << rt_val << endl;

			}else if(op == opCodes.MUL){
				long rd_val,rt_val,rs_val;
				rd_val = rd(memory[i]);
				rt_val = rt(memory[i]);
				rs_val = rs(memory[i]);

				print_instr32(memory[i]);
				out << "\t" << PC << "\t" ;
				out << "MUL R" << rd_val <<", R" << rs_val << ", R" << rt_val << endl;

			}else if(op == opCodes.AND){
				long rd_val,rt_val,rs_val;
				rd_val = rd(memory[i]);
				rt_val = rt(memory[i]);
				rs_val = rs(memory[i]);

				print_instr32(memory[i]);
				out << "\t" << PC << "\t" ;
				out << "AND R" << rd_val <<", R" << rs_val << ", R" << rt_val << endl;

			}else if(op == opCodes.OR){
				long rd_val,rt_val,rs_val;
				rd_val = rd(memory[i]);
				rt_val = rt(memory[i]);
				rs_val = rs(memory[i]);

				print_instr32(memory[i]);
				out << "\t" << PC << "\t" ;
				out << "OR R" << rd_val <<", R" << rs_val << ", R" << rt_val << endl;

			}else if(op == opCodes.XOR){
				long rd_val,rt_val,rs_val;
				rd_val = rd(memory[i]);
				rt_val = rt(memory[i]);
				rs_val = rs(memory[i]);

				print_instr32(memory[i]);
				out << "\t" << PC << "\t" ;
				out << "XOR R" << rd_val <<", R" << rs_val << ", R" << rt_val << endl;

			}else if(op == opCodes.NOR){
				long rd_val,rt_val,rs_val;
				rd_val = rd(memory[i]);
				rt_val = rt(memory[i]);
				rs_val = rs(memory[i]);

				print_instr32(memory[i]);
				out << "\t" << PC << "\t" ;
				out << "NOR R" << rd_val <<", R" << rs_val << ", R" << rt_val << endl;

			}else if(op == opCodes.SLT){
				long rd_val,rt_val,rs_val;
				rd_val = rd(memory[i]);
				rt_val = rt(memory[i]);
				rs_val = rs(memory[i]);

				print_instr32(memory[i]);
				out << "\t" << PC << "\t" ;
				out << "SLT R" << rd_val <<", R" << rs_val << ", R" << rt_val << endl;

			}else if(op == opCodes.ADDI){
				instr32 mask16("00000000000000001111111111111111");
				long offset;
				long rt_val,rs_val;
				rt_val = rt(memory[i]);
				rs_val = rs(memory[i]);

				temp = memory[i] & mask16;
				if(temp.bits[18] == 1){
					temp = ~ temp;
					temp = temp & mask16;
					temp = temp + instr32("00000000000000000000000000000001");
					offset = -temp.toNum();
				}else{
					offset = temp.toNum();

				}

				print_instr32(memory[i]);
				out << "\t" << PC << "\t" ;
				out << "ADDI R" << rt_val <<", R" << rs_val << ", #" << offset << endl;

			}else if(op == opCodes.ANDI){
				instr32 mask16("00000000000000001111111111111111");
				long offset;
				long rt_val,rs_val;
				rt_val = rt(memory[i]);
				rs_val = rs(memory[i]);

				temp = memory[i] & mask16;
				if(temp.bits[18] == 1){
					temp = ~ temp;
					temp = temp & mask16;
					temp = temp + instr32("00000000000000000000000000000001");
					offset = -temp.toNum();
				}else{
					offset = temp.toNum();

				}

				print_instr32(memory[i]);
				out << "\t" << PC << "\t" ;
				out << "ANDI R" << rt_val <<", R" << rs_val << ", #" << offset << endl;

			}else if(op == opCodes.ORI){
				instr32 mask16("00000000000000001111111111111111");
				long offset;
				long rt_val,rs_val;
				rt_val = rt(memory[i]);
				rs_val = rs(memory[i]);

				temp = memory[i] & mask16;
				if(temp.bits[18] == 1){
					temp = ~ temp;
					temp = temp & mask16;
					temp = temp + instr32("00000000000000000000000000000001");
					offset = -temp.toNum();
				}else{
					offset = temp.toNum();

				}

				print_instr32(memory[i]);
				out << "\t" << PC << "\t" ;
				out << "ORI R" << rt_val <<", R" << rs_val << ", #" << offset << endl;

			}else if(op == opCodes.XORI){
				instr32 mask16("00000000000000001111111111111111");
				long offset;
				long rt_val,rs_val;
				rt_val = rt(memory[i]);
				rs_val = rs(memory[i]);

				temp = memory[i] & mask16;
				if(temp.bits[18] == 1){
					temp = ~ temp;
					temp = temp & mask16;
					temp = temp + instr32("00000000000000000000000000000001");
					offset = -temp.toNum();
				}else{
					offset = temp.toNum();

				}

				print_instr32(memory[i]);
				out << "\t" << PC << "\t" ;
				out << "XORI R" << rt_val <<", R" << rs_val << ", #" << offset << endl;

			}
		}
		
	}
	
	//disassemble data segment to numbers
	void disassemble_data(){
		long num, PC;
		instr32 temp;
		int END_OF_INSTR = (data_offset-256)/4;

		//cout << code_size << endl;
		//cout << data_offset << endl;

		for(int i = END_OF_INSTR;i<code_size;i++){
			PC = 256 + i*4;
			temp.copy(memory[i]);

			if(temp.bits[0] == 1){
				temp = ~ temp;
				temp = temp + instr32("00000000000000000000000000000001");
				num = -temp.toNum();
			}else{
				num = temp.toNum();
			}

			print_instr32(memory[i]);
			out << "\t" << PC << "\t" ;
			out << num << endl;
		}

		out.close();
	}

	//function to create mask from instr32 object
	instr32 make_mask(int start,int end,instr32 ins){
		instr32 temp;
		for(int i=start;i<=end;i++)
			temp.bits[i] = 1;
		return temp;
	}
	
	//function to convert 2' instr32 object to long num
	long twos_complement_2_num(instr32 ins){
		instr32 temp;
		temp.copy(ins);

		if(ins.bits[0] == 1){
			temp = ~temp;
			temp = temp + instr32("00000000000000000000000000000001");
			return -temp.toNum();
		}else{
			return ins.toNum();
		}
	}

	//function to convert long num to 2' complement
	instr32 num_2_twos_complement(long num){
		instr32 temp;
		if(num < 0){
			num = 0 - num;
			//cout << num << endl;
			temp = num;
			//temp.print();
			//cout << endl;
			temp = num;
			temp = ~temp;
			temp = temp + instr32("00000000000000000000000000000001");
			return temp;

		}else{
			temp = num;
			return temp;
		}
	}

	void print_eight_data(int index){

		for(int i=index;i<index+8;i++){
			out2 << "\t" << twos_complement_2_num(memory[i]);
		}

	}
	
	//function to print data segment
	void print_data(){
		int END_OF_INSTR = (data_offset-256)/4;
		int count = 1;
		int offset = data_offset;
		out2 << "Data" << endl;

		for(int i=END_OF_INSTR;i<code_size;i++){
			out2 << offset << ":";
			print_eight_data(i);
			i = i + 7;
			offset =  (i+1)*4 + 252 + 4;
			out2 << endl;

		}

	}

	void print_eight_regs(int index){

		for(int i=index;i<index+8;i++){
			out2 << "\t" << twos_complement_2_num(R[i]);
		}

	}

	
	string pad_digit(int num){
		if(num > 9)
			return "";
		else
			return "0";
	}

	//function to print all registers values
	void print_regs(){
		out2 << "Registers" << endl;

		for(int i=0;i<32;i++){
			out2 << "R" << pad_digit(i) << i << ":";
			print_eight_regs(i);
			i = i + 7;
			out2 << endl;

		}
	}



	//function to get all instructions into instr_decoder object
	void decoder(){

		getDataOffset();
		int END_OF_INSTR = (data_offset-256)/4;
		instr32 mask;
		instr32 op, temp, tempPC;
		
		long PC = 256;

		mask = "11111100000000000000000000000000";

		//cout << "Data Offset = " << data_offset << endl;
		//cout << "END_OF_INSTR = " << END_OF_INSTR <<  endl;
		instr_decoded *insd;
		

		for(int i=0;i< END_OF_INSTR;i++){
			insd = new instr_decoded;
			PC = 256 + i*4;
			op = memory[i] & mask;

			if(op == opCodes.J){
				 
				instr32 mask4("11110000000000000000000000000000");
				instr32 mask26("00000011111111111111111111111111");

				temp = memory[i] & mask26;
				temp = temp << 2;
				//cout << (long)PC + 4 << endl;;
				tempPC = (long)PC + 4;
				tempPC = tempPC & mask4;
				temp = temp | tempPC;
				
				insd->ins.copy(opCodes.J);
				insd->signed_offset = temp.toNum();

				instr.push_back(insd);


			}else if(op == opCodes.JR){
				
				instr32 maskrs("00000011111000000000000000000000");

				temp = memory[i] & maskrs;
				temp = temp >> 21;
				
				insd->ins.copy(opCodes.JR);
				insd->rs = temp.toNum();

				instr.push_back(insd);
				

			}else if(op == opCodes.BEQ){
				
				instr32 mask16("00000000000000001111111111111111");
				long offset;
				long rs_val,rt_val;
				rs_val = rs(memory[i]);
				rt_val = rt(memory[i]);

				temp = memory[i] & mask16;
				temp = temp << 2;
				//cout << (long)PC + 4 << endl;;
				tempPC = (long)PC + 4;
				if(temp.bits[16] == 1){
					temp = ~ temp;
					instr32 mask18("00000000000000111111111111111111");
					temp = temp & mask18;
					temp = temp + instr32("00000000000000000000000000000001");
					offset = -temp.toNum();
				}else{
					offset = temp.toNum();

				}

				insd->ins.copy(opCodes.BEQ);
				insd->rs = rs_val;
				insd->rt = rt_val;
				insd->signed_offset = offset;

				instr.push_back(insd);
				

			}else if(op == opCodes.BLTZ){
				
				instr32 mask16("00000000000000001111111111111111");
				long offset;
				long rs_val;
				rs_val = rs(memory[i]);

				temp = memory[i] & mask16;
				temp = temp << 2;
				//cout << (long)PC + 4 << endl;;
				tempPC = (long)PC + 4;
				if(temp.bits[16] == 1){
					temp = ~ temp;
					instr32 mask18("00000000000000111111111111111111");
					temp = temp & mask18;
					temp = temp + instr32("00000000000000000000000000000001");
					offset = -temp.toNum();
				}else{
					offset = temp.toNum();

				}

				insd->ins.copy(opCodes.BLTZ);
				insd->rs = rs_val;
				insd->signed_offset = offset;

				instr.push_back(insd);
				

			}else if(op == opCodes.BGTZ){
				
				instr32 mask16("00000000000000001111111111111111");
				long offset;
				long rs_val;
				rs_val = rs(memory[i]);

				temp = memory[i] & mask16;
				temp = temp << 2;
				//cout << (long)PC + 4 << endl;;
				tempPC = (long)PC + 4;
				if(temp.bits[16] == 1){
					temp = ~ temp;
					instr32 mask18("00000000000000111111111111111111");
					temp = temp & mask18;
					temp = temp + instr32("00000000000000000000000000000001");
					offset = -temp.toNum();
				}else{
					offset = temp.toNum();

				}

				insd->ins.copy(opCodes.BGTZ);
				insd->rs = rs_val;
				insd->signed_offset = offset;

				instr.push_back(insd);
				

			}else if(op == opCodes.BREAK){
				
				insd->ins.copy(opCodes.BREAK);

				instr.push_back(insd);
				
				break;

			}else if(op == opCodes.SW){
				instr32 mask16("00000000000000001111111111111111");
				long offset;
				long rs_val,rt_val;
				rs_val = rs(memory[i]);
				rt_val = rt(memory[i]);

				temp = memory[i] & mask16;
				if(temp.bits[18] == 1){
					temp = ~ temp;
					temp = temp & mask16;
					temp = temp + instr32("00000000000000000000000000000001");
					offset = -temp.toNum();
				}else{
					offset = temp.toNum();

				}

				insd->ins.copy(opCodes.SW);
				insd->rs = rs_val;
				insd->rt = rt_val;
				insd->signed_offset = offset;

				instr.push_back(insd);


			}else if(op == opCodes.LW){
				instr32 mask16("00000000000000001111111111111111");
				long offset;
				long rs_val,rt_val;
				rs_val = rs(memory[i]);
				rt_val = rt(memory[i]);

				temp = memory[i] & mask16;
				if(temp.bits[18] == 1){
					temp = ~ temp;
					temp = temp & mask16;
					temp = temp + instr32("00000000000000000000000000000001");
					offset = -temp.toNum();
				}else{
					offset = temp.toNum();

				}

				insd->ins.copy(opCodes.LW);
				insd->rs = rs_val;
				insd->rt = rt_val;
				insd->signed_offset = offset;

				instr.push_back(insd);

			}else if(op == opCodes.SLL){
				instr32 mask16("00000000000000001111111111111111");
		
				long rd_val,rt_val,sa_val;
				rd_val = rd(memory[i]);
				rt_val = rt(memory[i]);
				sa_val = sa(memory[i]);

				insd->ins.copy(opCodes.SLL);
				insd->rd = rd_val;
				insd->rt = rt_val;
				insd->sa = sa_val;
				
				instr.push_back(insd);

			}else if(op == opCodes.SRL){
				instr32 mask16("00000000000000001111111111111111");
				
				long rd_val,rt_val,sa_val;
				rd_val = rd(memory[i]);
				rt_val = rt(memory[i]);
				sa_val = sa(memory[i]);

				insd->ins.copy(opCodes.SRL);
				insd->rd = rd_val;
				insd->rt = rt_val;
				insd->sa = sa_val;
				
				instr.push_back(insd);

			}else if(op == opCodes.SRA){
				instr32 mask16("00000000000000001111111111111111");
				long offset;
				long rd_val,rt_val,sa_val;
				rd_val = rd(memory[i]);
				rt_val = rt(memory[i]);
				sa_val = sa(memory[i]);

				insd->ins.copy(opCodes.SRA);
				insd->rd = rd_val;
				insd->rt = rt_val;
				insd->sa = sa_val;
				
				instr.push_back(insd);

			}else if(op == opCodes.NOP){
				memory[i].print();
				cout << "\t" << PC << "\t" ;
				cout << "NOP" << endl;

				insd->ins.copy(opCodes.NOP);
				
				instr.push_back(insd);

			}else if(op == opCodes.ADD){
				long rd_val,rt_val,rs_val;
				rd_val = rd(memory[i]);
				rt_val = rt(memory[i]);
				rs_val = rs(memory[i]);

				insd->ins.copy(opCodes.ADD);
				insd->rs = rs_val;
				insd->rt = rt_val;
				insd->rd = rd_val;
				
				instr.push_back(insd);

			}else if(op == opCodes.SUB){
				long rd_val,rt_val,rs_val;
				rd_val = rd(memory[i]);
				rt_val = rt(memory[i]);
				rs_val = rs(memory[i]);

				insd->ins.copy(opCodes.SUB);
				insd->rs = rs_val;
				insd->rt = rt_val;
				insd->rd = rd_val;
				
				instr.push_back(insd);

			}else if(op == opCodes.MUL){
				long rd_val,rt_val,rs_val;
				rd_val = rd(memory[i]);
				rt_val = rt(memory[i]);
				rs_val = rs(memory[i]);

				insd->ins.copy(opCodes.MUL);
				insd->rs = rs_val;
				insd->rt = rt_val;
				insd->rd = rd_val;
				
				instr.push_back(insd);

			}else if(op == opCodes.AND){
				long rd_val,rt_val,rs_val;
				rd_val = rd(memory[i]);
				rt_val = rt(memory[i]);
				rs_val = rs(memory[i]);

				insd->ins.copy(opCodes.AND);
				insd->rs = rs_val;
				insd->rt = rt_val;
				insd->rd = rd_val;
				
				instr.push_back(insd);

			}else if(op == opCodes.OR){
				long rd_val,rt_val,rs_val;
				rd_val = rd(memory[i]);
				rt_val = rt(memory[i]);
				rs_val = rs(memory[i]);

				insd->ins.copy(opCodes.OR);
				insd->rs = rs_val;
				insd->rt = rt_val;
				insd->rd = rd_val;
				
				instr.push_back(insd);

			}else if(op == opCodes.XOR){
				long rd_val,rt_val,rs_val;
				rd_val = rd(memory[i]);
				rt_val = rt(memory[i]);
				rs_val = rs(memory[i]);

				insd->ins.copy(opCodes.XOR);
				insd->rs = rs_val;
				insd->rt = rt_val;
				insd->rd = rd_val;
				
				instr.push_back(insd);

			}else if(op == opCodes.NOR){
				long rd_val,rt_val,rs_val;
				rd_val = rd(memory[i]);
				rt_val = rt(memory[i]);
				rs_val = rs(memory[i]);

				insd->ins.copy(opCodes.NOR);
				insd->rs = rs_val;
				insd->rt = rt_val;
				insd->rd = rd_val;
				
				instr.push_back(insd);

			}else if(op == opCodes.SLT){
				long rd_val,rt_val,rs_val;
				rd_val = rd(memory[i]);
				rt_val = rt(memory[i]);
				rs_val = rs(memory[i]);

				insd->ins.copy(opCodes.SLT);
				insd->rs = rs_val;
				insd->rt = rt_val;
				insd->rd = rd_val;
				
				instr.push_back(insd);

			}else if(op == opCodes.ADDI){
				instr32 mask16("00000000000000001111111111111111");
				long offset;
				long rt_val,rs_val;
				rt_val = rt(memory[i]);
				rs_val = rs(memory[i]);

				temp = memory[i] & mask16;
				if(temp.bits[18] == 1){
					temp = ~ temp;
					temp = temp & mask16;
					temp = temp + instr32("00000000000000000000000000000001");
					offset = -temp.toNum();
				}else{
					offset = temp.toNum();

				}

				insd->ins.copy(opCodes.ADDI);
				insd->rs = rs_val;
				insd->rt = rt_val;
				insd->signed_offset = offset;
				
				instr.push_back(insd);

			}else if(op == opCodes.ANDI){
				instr32 mask16("00000000000000001111111111111111");
				long offset;
				long rt_val,rs_val;
				rt_val = rt(memory[i]);
				rs_val = rs(memory[i]);

				temp = memory[i] & mask16;
				if(temp.bits[18] == 1){
					temp = ~ temp;
					temp = temp & mask16;
					temp = temp + instr32("00000000000000000000000000000001");
					offset = -temp.toNum();
				}else{
					offset = temp.toNum();

				}

				insd->ins.copy(opCodes.ANDI);
				insd->rs = rs_val;
				insd->rt = rt_val;
				insd->signed_offset = offset;
				
				instr.push_back(insd);

			}else if(op == opCodes.ORI){
				instr32 mask16("00000000000000001111111111111111");
				long offset;
				long rt_val,rs_val;
				rt_val = rt(memory[i]);
				rs_val = rs(memory[i]);

				temp = memory[i] & mask16;
				if(temp.bits[18] == 1){
					temp = ~ temp;
					temp = temp & mask16;
					temp = temp + instr32("00000000000000000000000000000001");
					offset = -temp.toNum();
				}else{
					offset = temp.toNum();

				}

				insd->ins.copy(opCodes.ORI);
				insd->rs = rs_val;
				insd->rt = rt_val;
				insd->signed_offset = offset;
				
				instr.push_back(insd);

			}else if(op == opCodes.XORI){
				instr32 mask16("00000000000000001111111111111111");
				long offset;
				long rt_val,rs_val;
				rt_val = rt(memory[i]);
				rs_val = rs(memory[i]);

				temp = memory[i] & mask16;
				if(temp.bits[18] == 1){
					temp = ~ temp;
					temp = temp & mask16;
					temp = temp + instr32("00000000000000000000000000000001");
					offset = -temp.toNum();
				}else{
					offset = temp.toNum();

				}

				insd->ins.copy(opCodes.XORI);
				insd->rs = rs_val;
				insd->rt = rt_val;
				insd->signed_offset = offset;
				
				instr.push_back(insd);

			}

			insd = NULL;
		}

	}
	
	//function to extract opcode from string
	string format(string str){
		stringstream ss;
		string new_str;
		bool flag = 0;
		for ( std::string::iterator it=str.begin(); it!=str.end(); ++it){
			if(*it == ' ' && flag == 0){
				ss << "\t";
				flag = 1;
			}else{
				ss << *it;
			}
		}
		new_str = ss.str();
		return new_str;
	}



	//function to simulate MIPS instructions
	void simulate(){
		int index = 0;
		int PC = 256;
		int PC_REC;
		instr_decoded *ptr;
		bool jump = 0;
		long jump_add = 0;
		int cycle = 0;

		bool BREAK = 0;
		

		while(1){

			++cycle;
			index = (PC - 256)/4;
			ptr = instr[index];
			PC_REC = PC;

			//cout << endl ;
			//ptr->ins.print();
			//cout << endl;
			//cout << "PC = " << PC << endl;
			if(ptr->ins == opCodes.J){
				PC = ptr->signed_offset - 4;

			}else if(ptr->ins == opCodes.JR){
				PC = twos_complement_2_num(R[ptr->rs]) - 4;
				

			}else if(ptr->ins == opCodes.BEQ){
				long rs_val = twos_complement_2_num(R[ptr->rs]);
				long rt_val = twos_complement_2_num(R[ptr->rt]);

				if(rs_val == rt_val){
					PC = PC + 4 + ptr->signed_offset - 4;
					
				}

			}else if(ptr->ins == opCodes.BLTZ){
				long rs_val = twos_complement_2_num(R[ptr->rs]);

				if(rs_val < 0){
					PC = PC + 4 + ptr->signed_offset - 4;
					
				}

			}else if(ptr->ins == opCodes.BGTZ){
				long rs_val = twos_complement_2_num(R[ptr->rs]);

				if(rs_val > 0){
					PC = PC + 4 + ptr->signed_offset - 4;
					
				}

			}else if(ptr->ins == opCodes.BREAK){

				BREAK = 1;

			}else if(ptr->ins == opCodes.SW){
				long rs_val = twos_complement_2_num(R[ptr->rs]);
				
				memory[((rs_val + ptr->signed_offset) - 256)/4] = R[ptr->rt];

			}else if(ptr->ins == opCodes.LW){
				long rs_val = twos_complement_2_num(R[ptr->rs]);
			
				R[ptr->rt] = memory[((rs_val + ptr->signed_offset) - 256)/4];
				//memory[rs_val + ptr->signed_offset].print();
				//cout << endl;
				//R[ptr->rt].print();
				//cout << endl;

			}else if(ptr->ins == opCodes.SLL){
				R[ptr->rd] = R[ptr->rt] << ptr->sa; 

			}else if(ptr->ins == opCodes.SRL){
				R[ptr->rd] = R[ptr->rt] >> ptr->sa; 

			}else if(ptr->ins == opCodes.SRA){
				R[ptr->rd] = R[ptr->rt].SRA(R[ptr->rt],ptr->sa);

			}else if(ptr->ins == opCodes.NOP){
				PC = PC + 4 - 4;

			}else if(ptr->ins == opCodes.ADD){
				R[ptr->rd] = R[ptr->rs] + R[ptr->rt];

			}else if(ptr->ins == opCodes.SUB){
				long rs_val = twos_complement_2_num(R[ptr->rs]);
				long rt_val = twos_complement_2_num(R[ptr->rt]);

				R[ptr->rd] = num_2_twos_complement(rs_val - rt_val);

			}else if(ptr->ins == opCodes.MUL){
				long rs_val = twos_complement_2_num(R[ptr->rs]);
				long rt_val = twos_complement_2_num(R[ptr->rt]);

				//cout << rs_val << endl;
				//cout << rt_val << endl;


				R[ptr->rd] = num_2_twos_complement(rs_val * rt_val);
				//R[ptr->rd].print();
				//cout << endl;

			}else if(ptr->ins == opCodes.AND){
				R[ptr->rd] = R[ptr->rs] & R[ptr->rt];

			}else if(ptr->ins == opCodes.OR){
				R[ptr->rd] = R[ptr->rs] | R[ptr->rt];

			}else if(ptr->ins == opCodes.XOR){
				R[ptr->rd] = R[ptr->rs] ^ R[ptr->rt];

			}else if(ptr->ins == opCodes.NOR){
				R[ptr->rd] = ~(R[ptr->rs] | R[ptr->rt]);

			}else if(ptr->ins == opCodes.SLT){
				long rs_val = twos_complement_2_num(R[ptr->rs]);
				long rt_val = twos_complement_2_num(R[ptr->rt]);

				if(rs_val < rt_val){
					R[ptr->rd] = 1;
				}

			}else if(ptr->ins == opCodes.ADDI){
				long rs_val = twos_complement_2_num(R[ptr->rs]);
				long rt_val = twos_complement_2_num(R[ptr->rt]);

				R[ptr->rt] = R[ptr->rs] + num_2_twos_complement(ptr->signed_offset);

			}else if(ptr->ins == opCodes.ANDI){
				long rs_val = twos_complement_2_num(R[ptr->rs]);
				long rt_val = twos_complement_2_num(R[ptr->rt]);

				R[ptr->rt] = R[ptr->rs] & num_2_twos_complement(ptr->signed_offset);

			}else if(ptr->ins == opCodes.ORI){
				long rs_val = twos_complement_2_num(R[ptr->rs]);
				long rt_val = twos_complement_2_num(R[ptr->rt]);

				R[ptr->rt] = R[ptr->rs] | num_2_twos_complement(ptr->signed_offset);

			}else if(ptr->ins == opCodes.XORI){
				long rs_val = twos_complement_2_num(R[ptr->rs]);
				long rt_val = twos_complement_2_num(R[ptr->rt]);

				R[ptr->rt] = R[ptr->rs] ^ num_2_twos_complement(ptr->signed_offset);

			}

			
			
			out2 << "--------------------" << endl;

			out2 << "Cycle:" << cycle << format(m2c[PC_REC].substr(32)) << endl << endl;
			print_regs();
			out2 << endl;
			print_data();
			out2 << endl;

			PC = PC + 4;
			if(BREAK)
				break;

		}

		out2.close();

	}

	//function to create memory -> instruction map
	void create_map(){
		string line;
  		ifstream myfile;
  		myfile.open("generated_disassembly.txt");
  		int PC = 256;
  		int i = 0;
    	while ( i < code_size ){

      		getline (myfile,line);
      		
      		m2c.insert ( pair<int,string>(PC + i*4,line) );

      		i++;
    	}
    	myfile.close();
	}

};



// main function
int main(int argc, char* argv[]){

	if(argc < 2){
		cout << "Usage: ./MIPSsim <file>" << endl;
	}else{
		Dissassembler dis;
		dis.file2memory(argv[1]);
		dis.disassemble_instructions();
		dis.disassemble_data();
		dis.decoder();
		dis.create_map();
		dis.simulate();
	}
	


	/*
	cout << "--------------------------------------------------------" << endl;
	instr32 ins = dis.make_mask(1,4,instr32("10101010101010101010101010101010"));
	ins.print();	cout << endl;

	ins = dis.num_2_twos_complement(-1);
	ins.print();	cout << endl;

	cout << dis.twos_complement_2_num(instr32("11111111111111111111111111111111")) << endl;

	instr32 one, two;
	one = dis.num_2_twos_complement(-1);
	two = dis.num_2_twos_complement(-3);
	ins = one + two;

	cout << dis.twos_complement_2_num(ins) << endl;

	dis.print_data();
	cout << endl << endl;
	dis.print_regs();
	
	instr32 ins("00001111111111111111111111111111");
	ins = ins.SRA(ins,3);
	ins.print();
	cout << endl;
	*/
	return 0;
}
