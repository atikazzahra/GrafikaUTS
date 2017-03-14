sudo ./overlap
sudo ./intro
sudo ./rolling-game
OUT=$?
if [ $OUT -eq 0 ];
then
	sudo ./trans1
	sudo ./shooter-game
	OUT=$?
	if [ $OUT -eq 0 ];
	then
		sudo ./trans2
		sudo ./map-game
		OUT=$?
		if [ $OUT -eq 0 ];
		then
			sudo ./finish
		else
			sudo ./game-over
		fi
	else 
		sudo ./game-over
	fi
	
else
	sudo ./game-over
fi
