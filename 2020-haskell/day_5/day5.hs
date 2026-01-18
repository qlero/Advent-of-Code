import qualified Data.List as L
import Data.List.Split ( splitOn )

readContent :: IO [[Char]]
readContent = splitOn "\n" <$> readFile "input.txt"

foldl' :: (t -> a -> t) -> t -> [a] -> t
foldl' f z []     = z
foldl' f z (x:xs) = let z' = z `f` x 
                    in seq z' $ foldl' f z' xs

checker :: [Int] -> Char -> [Int] 
checker range char
    | char == 'B' || char == 'R' = [lowerBound + (upperBound-lowerBound) `div` 2, upperBound]
    | char == 'F' || char == 'L' = [lowerBound, (upperBound-lowerBound) `div` 2 + lowerBound]
    | otherwise = range
  where 
      lowerBound = head range
      upperBound = last range

processBoardingPass :: [Char] -> Int
processBoardingPass pass = row * 8 + column
  where
      row = last $ foldl' checker [0,127] $ take 7 pass
      column = last $ foldl' checker [0,7] $ drop 7 pass

maxID :: [Int] -> Int
maxID = foldl' max 0

findSeat :: [Int] -> Int
findSeat [] = 0
findSeat [x] = 0
findSeat (x:xs)
  | head xs == (x+2) = x+1
  | otherwise = findSeat xs

main :: IO()
main = do
    boardingPasses <- readContent
    print $ maxID $ map processBoardingPass boardingPasses
    print $ findSeat $ L.sort $ map processBoardingPass boardingPasses