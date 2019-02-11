module SPI_Slave(clk,sent_data, SCK, SSEL, MOSI,MISO,rev_data,interrupt);
 input SCK, SSEL, MOSI,clk;
 input[31:0] sent_data;
 output  MISO;
 output  interrupt;
 reg [7:0] byte_data_received;
 output reg [7:0]rev_data;
 reg [31:0] byte_data_sent;

 reg [1:0]bSSEL;
 reg [1:0]bSCK;
 reg [2:0]cnt;
 reg [1:0]bresevend;
 wire select=(bSSEL==2'b10);
 wire relese=(bSSEL==2'b01);
 wire selecting=(SSEL==0);
 wire read=selecting && sckup;
 wire sckdown =(bSCK==2'b10);
 wire sckup=(bSCK==2'b01);
 wire send=selecting && sckdown;
 wire resevend=read&&(cnt==3'b111);
 assign interrupt=(bresevend==2'b01);
 always @(posedge clk) begin
	bSSEL<={bSSEL[0],SSEL}; 
 end
 
 always @(posedge clk) begin
	bSCK<={bSCK[0],SCK};
 end
 
 always @(posedge clk) begin
	bresevend<={bresevend[0],resevend};
 end
 
 
 always @(posedge clk) begin
	if(select) begin
		cnt<=3'b000;
	end
	
	if(relese) begin
		byte_data_sent<=8'b00000000;
		byte_data_sent<=sent_data;
	end
	
	if(send) begin
		byte_data_sent<={byte_data_sent[30:0],1'b0};
	end
	
	if(read) begin
		cnt<=cnt+3'b001;
		byte_data_received<={byte_data_received[6:0],MOSI};
	end
	
	if(interrupt) begin
		rev_data<=byte_data_received;
		cnt<=3'b000;
	end	
end
assign MISO=byte_data_sent[31];
endmodule
