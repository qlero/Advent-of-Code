convertToInt :: String -> Int
convertToInt str = read str :: Int

to2020 :: Int -> Int
to2020 val = 2020 - val

readInput :: String -> [Int]
readInput lst = map convertToInt $ lines lst

-- pairs
 
filterCommon :: [Int] -> [Int] -> [Int]
filterCommon xs ys = filter (\x -> x `elem` ys) xs

sharedElements :: (Int -> Int) -> [Int] -> [Int]
sharedElements func lst =  filterCommon lst $ map func $ lst

multAnswer1 :: String -> Int
multAnswer1 lst = 
    foldl (*) 1 $ sharedElements to2020 $ readInput lst

-- trios

functorMult :: [Int] -> [Int]
functorMult lst = (map (-) $ map to2020 lst) <*> lst

multAnswer2 :: String -> Int
multAnswer2 lst = 
    foldl (*) 1 $ filterCommon (readInput lst) $ functorMult $ readInput lst

main :: IO ()
main = do
    ls <- readFile "input.txt"
    print $ multAnswer2 ls