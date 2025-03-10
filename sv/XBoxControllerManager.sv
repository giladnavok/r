module XBoxControllerManager (
	input logic HPS_USB_CLKOUT,
	input logic resetN,
	input logic transmitEnd,
	input logic [511:0] recieveBuffer,
	input logic recieveSize,
	
	output logic [511:0] transmitBuffer,
	output logic [9:0] transmitSize,
	output logic startTransmit
);

localparam SET_CONFIGURATION_REQUEST = 36'h00001c0030ea1efa0c82ffff000000000000001000010001000002080000000000090100002000000000;
localparam SET_CONFIGURATION_REQUEST_SIZE = 36;

localparam CLOCK_FREQUENCY = 50_000_000;
localparam SLEEP_SECS = 3;
localparam SLEEP_CYCLES = SLEEP_SECS * CLOCK_FREQUENCY;

enum logic {S_SET, S_SLEEP} STATE;

logic [31:0] counter;

always_ff @(posedge HPS_USB_CLKOUT, negedge resetN) begin
	if (resetN == 1'b0) begin
		transmitBuffer <= 0;
		transmitSize <= 0;
		startTransmit <= 0;
		counter <= 0;
		STATE <= S_SLEEP;
	end

	startTransmit <= 1'b0;
	transmitBuffer <= 0;
	transmitSize <= 0;

	case(STATE)
		S_SLEEP: begin
			if (counter >= SLEEP_CYCLES) begin
				transmitBuffer <= SET_CONFIGURATION_REQUEST;
				transmitSize <= SET_CONFIGURATION_REQUEST;
				startTransmit <= 1'b1;
				counter <= 0;
				STATE <= S_SET;
			end else begin
				counter <= counter + 1;
			end
		end

		S_SET: begin
			transmitBuffer <= SET_CONFIGURATION_REQUEST;
			transmitSize <= SET_CONFIGURATION_REQUEST;
			counter <= counter + 1;
			if (transmitEnd) begin
				STATE <= S_SLEEP;
			end else if (counter >= SLEEP_CYCLES) begin
				counter <= 0;
				STATE <= S_SLEEP;
			end
		end

	endcase
end

endmodule

			
			




