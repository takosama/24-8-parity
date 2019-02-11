module BCH24_32(in,out);


input [23:0] in;
output wire [31:0] out={in[23:0],
	in[0]^in[1]^in[2]^in[3]^in[4],
	in[5]^in[6]^in[7]^in[8]^in[9],
	in[10]^in[11]^in[12]^in[13]^in[14],
	in[15]^in[16]^in[17]^in[18]^in[19],
	in[0]^in[5]^in[10]^in[15]^in[20],
	in[1]^in[6]^in[11]^in[16]^in[21],
	in[2]^in[7]^in[12]^in[17]^in[22],
	in[3]^in[8]^in[13]^in[18]^in[23]};
		

endmodule
