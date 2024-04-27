TIMEOUT(900000);

var nNodes = mote.getSimulation().getMotes().length;
//log.log("Motes:" + nNodes + "\n");

var n = nNodes +1;
var sTime = new Array(n);
var rTime = new Array(n);
var sPacket = new Array(n);
var rPacket = new Array(n);
var aux = 0;

for (aux = 0; aux <= nNodes; aux++)
{
		sTime[aux] = 0;
		rTime[aux] = 0;
		sPacket[aux] = 0;
		rPacket[aux] = 0;
}

log.log("##" + "Time PRR" + "\n");

while (true) 
{	
	//log.log(time + ";" + id + ";" + msg + "\n");
	//log.log(msg + "\n");

	if (msg.substring(0,2)=='S:')
	{
			sPacket[id] = sPacket[id] + 1;
			//log.log(id + " S: " + sPacket[id] + "\n");
			//log.log("sPacket: " + sPacket.toString() + "\n");
	}
	
	if (msg.substring(4,6)=='R:')
	{
			//log.log("MSG: " + msg + "\n");
			//aux = msg.length();
			//aux = parseInt(msg.substring(aux-2,aux), 16);
			aux = parseInt(msg.substring(13,15), 16);
            		//log.log("Sender ID: " + aux + "\n");			

			rPacket[aux] = rPacket[aux] + 1;
			//log.log(aux + " R: " + rPacket[aux] + "\n");
			//log.log("rPacket: " + rPacket.toString() + "\n");

			var i;
			aux = 0;
			for (i = 2; i <= nNodes; i++)
			{
					aux = aux + (parseInt(rPacket[i]) / parseInt(sPacket[i]));
					//log.log("aux = " + aux + "\n");
			}
			if (!isNaN(aux) && isFinite(aux))
			{
				log.log((time/1000000) + " " + (aux / (nNodes - 1)) * 100 + "\n");
			}
	}

   YIELD();
}
