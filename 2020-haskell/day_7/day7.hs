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
    | otherwise        = concatMap (replicate (read occurence :: Int)) [(bag, bag, [subBag])] 
  where
    occurence = fst occurences
    subBag = snd occurences

parseLineDuplicates :: String -> [Instruction]
parseLineDuplicates ln = concatMap (createInstructions $ head bagColors) occurences 
    where
      splitLine = init $ splitOn " bag" ln
      splitItems = (:) (head splitLine) <$> fmap lines (tail splitLine)
      bagNumber = fmap (last . take 3 . reverse . splitOn " " . head .  tail) splitItems
      bagColors = fmap (concat . reverse . take 2 . reverse . splitOn " ") splitLine
      occurences = zip bagNumber $ tail bagColors

countComponents :: Bool -> [Instruction] -> Maybe Int
countComponents invert instructionSet = output
  where 
    (graph, nodeFromVertex, vertexFromKey) = graphFromEdges instructionSet
    shinyGoldVertex = vertexFromKey "shinygold"
    finalGraph 
      | invert    = transposeG graph
      | otherwise = graph
    output = fmap (\x -> x-1) $ length . reachable finalGraph <$> shinyGoldVertex

recursiveCount :: [(Instruction, Int)] -> (Int, String) -> Int
recursiveCount dataset (holdValue, name) = (+) (sum bagNumber) recursiveBit
  where
    filteredDataset = filter (\((_, _, [z]), _) -> z /= "noother") $ 
      filter (\((x, _, _), _) -> x == name) dataset
    bagNumber = map (\((_,_,_),t) -> holdValue * t) filteredDataset
    nextStep = zip bagNumber $ map (\((_, _, [z]), _) -> z) filteredDataset
    recursiveBit = sum $ map (recursiveCount dataset) nextStep

main :: IO()
main = do
    instructions <- readContent
    let mapIns = map (\x -> (head x, length x)) . group . sort $ concatMap parseLineDuplicates instructions
    print $ countComponents True (map parseLine instructions) 
    print $ recursiveCount mapIns (1, "shinygold")


