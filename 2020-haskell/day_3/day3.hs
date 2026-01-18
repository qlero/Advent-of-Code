import Data.List (genericIndex)

type Index = Int
type Slope = Int
type MoveDown = Int

cycleElement :: [Char] -> Int -> Int
cycleElement element index = tree
    where 
        list = cycle element
        item = list `genericIndex` index
        tree = 
            if item == '#'
            then 1
            else 0

recursiveRead :: [[Char]] -> Index -> (Slope, MoveDown) -> [Int]
recursiveRead [] _ _ = []
recursiveRead (x:xs) index strategy = processedArea : nextArea
    where 
        slope = fst strategy
        nextList = 
            if length xs < 2
            then []
            else tail xs
        foreground = 
            if snd strategy == 1
            then xs
            else nextList
        processedArea = cycleElement x index
        nextArea = recursiveRead foreground (index + slope) strategy

main :: IO ()
main = do
    ls <- readFile "input.txt"
    let unpackedLs = lines ls
    let strategy = [(1,1), (3,1), (5,1), (7,1), (1,2)]::[(Slope, MoveDown)]
    let processing = recursiveRead unpackedLs 0 
    print $ (foldl (*) 1) $ map (foldl (+) 0) $ map processing strategy