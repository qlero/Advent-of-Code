import Data.List.Split ( splitOn ) 
import Control.Lens ( (&), (.~), element ) 

type Instruction = String
type Memory = [Int]
type Accumulator = Int
type State = (Int, Int) -- (currentAccumulator, Index)

readContent :: IO [Instruction]
readContent = splitOn "\n" <$> readFile "input.txt"

-- part 1

newRead :: String -> Int
newRead ('+':xs) = read xs::Int
newRead ('-':xs) = -(read xs::Int)

parseInstruction :: State -> Instruction -> State
parseInstruction state instruction = (newAccumulator, newIndex)
  where
    parsedIn = splitOn " " instruction
    newAccumulator
      | head parsedIn == "acc" = (+) (fst state) (newRead $ last parsedIn)
      | otherwise              = fst state 
    newIndex
      | head parsedIn == "jmp" = max 0 $ (+) (snd state) (newRead $ last parsedIn)
      | otherwise              = (+) (snd state) 1

runBoot :: [Instruction] -> Memory -> State -> String
runBoot instructions memory state
    | currentIndex == length instructions  = show (fst state)
    | currentIndex > length instructions   = "early stop: " ++ show (fst state)
    | currentIndex `elem` memory           = "early stop: " ++ show (fst state)
    | length instructions == length memory = "early stop: " ++ show (fst state)
    | otherwise                            = runBoot instructions newMemory newState 
  where
    currentIndex = snd state
    newMemory = currentIndex : memory
    newState = parseInstruction state $ instructions !! currentIndex 

-- part 2

instructionType :: Instruction -> String
instructionType = head . splitOn " "

countNopJmp :: [Instruction] -> Memory -> Int -> Memory
countNopJmp instructions memory index
    | null instructions = memory
    | otherwise         = countNopJmp (tail instructions) newMemory (index+1)
  where 
    insType = instructionType $ head instructions
    newMemory
      | insType == "nop" || insType == "jmp" = index : memory
      | otherwise                            = memory

replaceElement :: [Instruction] -> Int -> [Instruction]
replaceElement instructions index = instructions & element index .~ newValue
  where 
    value = instructions !! index
    insType = instructionType value
    insIncr = last $ splitOn " " value
    newValue
      | insType == "nop" = "jmp " ++ insIncr
      | otherwise        = "nop " ++ insIncr              

replaceInstance :: Memory -> [Instruction] -> [[Instruction]]
replaceInstance memory instructions = instructionsSet
  where
    instructionsSet = map (replaceElement instructions) memory

findTerminalValues :: [Instruction] -> [String]
findTerminalValues instructions = map (\ins -> runBoot ins [] (0,0)) $ instructionCombinations
  where 
    instructionCombinations = replaceInstance (countNopJmp instructions [] 0) instructions

main :: IO()
main = do
    instructions <- readContent
    print $ runBoot instructions [] (0,0)
    print $ filter (\x -> take 1 x /= "e") $ findTerminalValues instructions