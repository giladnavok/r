module USBTransceiver (
	input logic resetN,
	input logic HPS_USB_CLKOUT,
	input logic HPS_USB_DIR,
	input logic HPS_USB_NXT,
	inout logic [7:0] HPS_USB_DATA,

	output logic HPS_USB_RESET,
	output logic HPS_USB_STP,


	input logic [511:0]	dataBufferIn,
	input logic	startTransmit,
	input logic [8:0] dataSizeIn,

	output logic [511:0] dataBufferOut,
	output logic [8:0] dataSizeOut,
	output logic dataValidOut
);


enum logic [2:0] {S_SET_RESET, S_RESET, S_IDLE, S_READ, S_READ_BYTE, S_WRITE, S_WRITE_BYTE} STATE;


localparam DIR_WRITE = 1'b0;
localparam DIR_READ = 1'b1;

logic [7:0] dataWrite;
logic [7:0] dataRead;

assign dataRead =  (HPS_USB_DIR == DIR_READ)  ?   HPS_USB_DATA : 8'h00;
assign HPS_USB_DATA = (HPS_USB_DIR == DIR_WRITE) ? dataWrite : 8'bz;

localparam [1:0] READ_END_IDLE_PERIOD = 2'b11;
localparam [1:0] WRITE_HOLD_CYCLES = 2'b01;

logic [1:0] resetTimer;

logic [10:0] currentByteCount;
logic [7:0] byteBuffer;
logic [1:0] readIdleCycles;
logic [1:0] writeHoldCycles;

always_ff @(posedge HPS_USB_CLKOUT or negedge  resetN)
begin
	if (resetN == 1'b0) begin
		STATE <= S_SET_RESET;
		HPS_USB_STP <= 1'b0;
		dataValidOut <= 1'b0;
		currentByteCount <= 0;
	end
	else begin

		HPS_USB_RESET <= 1'b0;

		case(STATE)
			S_SET_RESET: begin
				resetTimer <= 2'b11;
				STATE <= S_RESET;
				HPS_USB_RESET <= 1'b1;
			end
			S_RESET: begin
				HPS_USB_RESET <= 1'b1;
				resetTimer -= 1'b1;
				if (resetTimer == 2'b00) begin
					STATE <= S_IDLE;
				end
			end
			S_IDLE: begin
				HPS_USB_STP <= 1'b0;
				currentByteCount <= 0;
				if (HPS_USB_DIR == DIR_READ && HPS_USB_NXT) begin
					STATE <= S_READ_BYTE;
					dataValidOut <= 1'b0;
				end else if (HPS_USB_DIR == DIR_WRITE && startTransmit) begin
					STATE <= S_WRITE;
				end
				
			end

			S_READ_BYTE: begin
				byteBuffer <= dataRead;
				if (HPS_USB_NXT == 1'b0) begin
					dataBufferOut[currentByteCount*8] <= byteBuffer[0];
					dataBufferOut[currentByteCount*8 + 1] <= byteBuffer[1];
					dataBufferOut[currentByteCount*8 + 2] <= byteBuffer[2];
					dataBufferOut[currentByteCount*8 + 3] <= byteBuffer[3];
					dataBufferOut[currentByteCount*8 + 4] <= byteBuffer[4];
					dataBufferOut[currentByteCount*8 + 5] <= byteBuffer[5];
					dataBufferOut[currentByteCount*8 + 6] <= byteBuffer[6];
					dataBufferOut[currentByteCount*8 + 7] <= byteBuffer[7];
					currentByteCount <= currentByteCount + 1;
					readIdleCycles <= 1'b11;
					STATE <= S_READ;
				end
			end

			S_READ: begin
				if (HPS_USB_NXT == 1'b1) begin
					STATE <= S_READ_BYTE;
				end else begin
					if (readIdleCycles == 0) begin
						dataSizeOut <= currentByteCount;
						dataValidOut <= 1'b1;
						STATE <= S_IDLE;
					end else begin
						readIdleCycles <= readIdleCycles - 1;
					end
				end
			end

			S_WRITE_BYTE: begin
				dataWrite[0] <= dataBufferIn[currentByteCount*8];
				dataWrite[1] <= dataBufferIn[currentByteCount*8 + 1];
				dataWrite[2] <= dataBufferIn[currentByteCount*8 + 2];
				dataWrite[3] <= dataBufferIn[currentByteCount*8 + 3];
				dataWrite[4] <= dataBufferIn[currentByteCount*8 + 4];
				dataWrite[5] <= dataBufferIn[currentByteCount*8 + 5];
				dataWrite[6] <= dataBufferIn[currentByteCount*8 + 6];
				dataWrite[7] <= dataBufferIn[currentByteCount*8 + 7];
				
				if (HPS_USB_NXT == 1'b1) begin
					currentByteCount <= currentByteCount + 1;
					STATE <= S_WRITE;
				end
			end

			S_WRITE: begin
				if (currentByteCount < dataSizeIn) begin
					if (HPS_USB_NXT == 1'b0) begin
						STATE <= S_WRITE_BYTE;
					end
				end else begin
					HPS_USB_STP <= 1'b1;
					STATE <= S_IDLE;
				end
			end
			endcase
		end
end
endmodule
					
					

					

