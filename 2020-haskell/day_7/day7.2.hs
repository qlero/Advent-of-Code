import Data.List.Split ( splitOn )
import Data.Graph ( graphFromEdges, transposeG, reachable )
import Data.List ( group, sort )

type Instruction = (String, String, [String]) 

readContent :: IO [String]
readContent = splitOn "\n" <$> readFile "input.txt"

parseLine :: String -> Instruction
parseLine ln = output
  where
    splitLine = init $ splitOn " bag" ln
    bagColors = fmap (concat . reverse . take 2 . reverse . splitOn " ") splitLine
    output = (head bagColors, head bagColors, tail bagColors)

createInstructions :: String -> (String, String) -> [Instruction]
createInstructions bag occurences
    | occurence == "contain" = [(bag, bag, [subBag])]
    | otherwise              = concatMap (replicate (read occurence :: Int)) [(bag, bag, [subBag])] 
  where
    occurence = fst occurences
    subBag = snd occurences

countComponents :: Bool -> [Instruction] -> Maybe Int
countComponents invert instructionSet = output
  where 
    (graph, nodeFromVertex, vertexFromKey) = graphFromEdges instructionSet
    shinyGoldVertex = vertexFromKey "shinygold"
    output = fmap (\x -> x-1) $ length . reachable (transposeG graph) <$> shinyGoldVertex

parseLineDuplicates :: String -> [Instruction]
parseLineDuplicates ln = concatMap (createInstructions $ head bagColors) occurences 
    where
      splitLine = init $ splitOn " bag" ln
      splitItems = (:) (head splitLine) <$> fmap lines (tail splitLine)
      bagNumber = fmap (last . take 3 . reverse . splitOn " " . head .  tail) splitItems
      bagColors = fmap (concat . reverse . take 2 . reverse . splitOn " ") splitLine
      occurences = zip bagNumber $ tail bagColors

slimInstructions :: [String] -> [(String, String, Int)]
slimInstructions instructions = filteredInstructions
  where
    parsedInstructions = concatMap parseLineDuplicates instructions
    mapInstructions = map (\x -> (head x, length x)) . group . sort $ parsedInstructions
    filteredInstructions = map (\((x, _, [z]),t)->(x,z,t)) mapInstructions

recursiveCount :: [(String, String, Int)] -> (Int, String) -> Int
recursiveCount dataset (holdValue, name) = (+) (sum bagNumber) recursiveBit
  where
    filteredDataset = filter (\(x,y,_) -> y /= "noother" && x == name) dataset
    bagNumber = map (\(_,_,z) -> holdValue * z) filteredDataset
    nextStep = zip bagNumber $ map (\(_,y,_) -> y) filteredDataset
    recursiveBit = sum $ map (recursiveCount dataset) nextStep

main :: IO()
main = do
    instructions <- readContent
    print $ countComponents True (map parseLine instructions) 
    print $ recursiveCount (slimInstructions instructions) (1, "shinygold")