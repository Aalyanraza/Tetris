/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 *
*/

//---Piece Starts to Fall When Game Starts---//
void fallingPiece(float& timer, float& delay, int& colorNum)
{
    if (timer>delay)
    {
        for (int i=0;i<4;i++)
        {
                point_2[i][0]=point_1[i][0];
                point_2[i][1]=point_1[i][1];
                point_1[i][1]+=1;                   //How much units downward
        }
        if (!anamoly())
        {
            for ( int i=0; i<4; i++)
                gameGrid[point_2[i][1]][point_2[i][0]]= colorNum;
            colorNum= 1+ rand()%7;
            int n=rand()%7;
            for (int i=0;i<4;i++)
            {
                    point_1[i][0] = BLOCKS[n][i] % 2;
                    point_1[i][1] = BLOCKS[n][i] / 2;
            }
        }
        timer=0;        
    }
}
/////////////////////////////////////////////
///*** START CODING YOUR FUNCTIONS HERE ***///
void delayreset( float &delay )
{
    if ( point_1[0][1]==0)
        delay=0.3;
}
void leftborder( int &x)                                       //to hold left border
{
    if ( x==-1 )
    {
        bool flag=0;
        for ( int i=0; i<4; i++)
        {
            if ( point_1[i][0]==0 )                           //aside left border
                flag= true;
        }
        if (flag)
            x=0;                                              //going left not possible 
        flag=0;    
    }
}
void rightborder( int &x)                                      //to hold right border
{
    if ( x==1 )
    {
        bool flag=0;
        for ( int i=0; i<4; i++ )                              //to check each coordinate
        {
            if ( point_1[i][0]==9 )                            //aside right border
                flag= true;
        }
        if (flag)
            x=0;                                               //going right not possible
        flag=0;
    }
}
void overlapprevention(int& x)
{
    for(int i=0;i<4;i++)
    { 
        int row=point_1[i][1];
        int column=point_1[i][0];
        if (x==1)                                              //command to go right
        {  
            if (gameGrid[row][column+1]!=0)                    //color at right
                x=0;                                           //not possible
        }
        else if ( x==-1)                                       //command to go left
        {  
            if (gameGrid[row][column-1]!=0)                    //checking if color at left
                x=0;                                           //cannot go left 
        }

    }
}
void leftright( int &x, int& colorNum)                         //to move horizontally
{   

    for (int i=0;i<4;i++)
    {
        point_1[i][0]+= (x);                                   //x is +ve for right and -ve for left           
    }  
    x=0;    
}
void turn( bool& rotate)                                       // to rotate   
{   
    if (rotate)
    {
        bool flag=1;
        for (int i=0;i<4;i++)
        { 
            point_2[i][0]=point_1[i][0];                      //duplicate point_1
            point_2[i][1]=point_1[i][1];
        }
        for (int i=0;i<4;i++){
            int fr1= point_2[i][1]-point_2[0][1];               //rotate duplicate 
            int fr2= point_2[i][0]-point_2[0][0];
            point_2[i][0]=point_2[0][0]+fr1;
            point_2[i][1]=point_2[0][1]+fr2;
        }
        for (int i=0;i<4;i++){
            if (point_2[i][0]<0 || point_2[i][0]>9)          //check boundaries
                flag=0;    
        }
        if (flag==1)                                          //copy if boxes are within boundaries
        {
            for (int i=0;i<4;i++)
            {
                point_1[i][0] =point_2[i][0];
                point_1[i][1] =point_2[i][1]; 
            }
        } 
        rotate=0;
    }
}
int countscore(int count)                                      //to calculate score
{
    switch (count)
    {
        case 0:                                                 //no line pops
            return 0;
        case 1:                                                 //1 line pops
            return 10;
        case 2:                                                 //2 line pops
            return 30;
        case 3:                                                 //3 line pops 
            return 60;
        case 4:                                                 //4 line pops
            return 100;
    }
return 0;} 
void blast(int& score)                                        //to destroy filled rows
{
    int count=0;
    for (int i=19; i>=0; i--)                                  //to check each row
    {
        bool flag=1;
        for (int j=0; j<10; j++)                               //to check each column    
        {   
            if ( gameGrid[i][j]==0 )                           //if any one is unfilled            
                flag=0;
        }  
        if (flag)                                              //whole row is filled             
        {
            count++;
            for (int j=0; j<10; j++)
            {
                gameGrid[i][j]=0;                              //empty the whole row 
            }
            for (int k=i; k>=01; k--)
            {
                for (int j=0; j<10; j++)
                {   
                    gameGrid[k][j]=gameGrid[k-1][j];           //upper rows fall 
                }    
            }
        }
    }
    score +=countscore(count);
} 
void shadow()
{
    int column,row,s=0;                                    
    for (int i=0;i<4;i++)
    {
        column=point_1[i][0];
        row=point_1[i][1];
        for (int j=row; j<=19;j++)
        {
            s=0;
            if (gameGrid[j][column]==0)
            {
                s=j;
            }    
        }
        gameGrid[s][column]=1;
    }
}
void append( int score)
{
    std::fstream file("file.txt");
    file<<score<<std::endl;
     
file.close();
}
bool end()                                                   // to end game
{
    bool flag=1;
    for (int j=0; j<10; j++)                               //to check each column    
    {   
        if ( gameGrid[0][j]!=0 )                           //if first row is not empty            
            flag=0;
    }
return flag;     
}
void highscore()
{
    int score1[100];
 
    std::ifstream infile("file.txt");                       //input
    int index=0;
    while(infile>>score1[index])
    {
        index++;
    }
    infile.close();
    
    for( int i=0; i<index; i++)                            //decending order
	{		
		for(int j=i+1; j<index; j++)
		{
            int temp=0;
			if(score1[i]<score1[j])
			{
				temp  =score1[i];
				score1[i]=score1[j];
				score1[j]=temp;
			}
		}
	}

    for(int i=0; i<index && i<10; i++)                            //display
		std::cout<<i+1<<". "<<score1[i]<<std::endl;
}
///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////