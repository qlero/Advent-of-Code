import Data.List.Split ( splitOn )
import Data.List ( sort, group )

type Keys = [Int]
type PreambleLength = Int

readContent :: IO [Int]
readContent = map read . splitOn "\n" <$> readFile "input.txt"

-- part 1

removeDuplicates :: Keys -> Keys
removeDuplicates = map head . group . sort

combinator :: Keys -> PreambleLength -> Keys
combinator keys preambleLength = combinations 
  where
    preamble = take preambleLength keys
    combinations = removeDuplicates $ map (+) preamble <*> preamble

checker :: Keys -> Keys -> PreambleLength -> Keys
checker keys memory preambleLength 
    | length keys == preambleLength = memory
    | otherwise                     = checker (tail keys) newMemory preambleLength
  where 
    validKeys = combinator keys preambleLength
    keyToCheck = last $ take (preambleLength + 1) keys
    newMemory 
      | keyToCheck `notElem` validKeys = keyToCheck : memory
      | otherwise                      = memory

-- part 2

checkSums :: Keys -> Int -> PreambleLength -> (Bool, [Int])
checkSums keys valueToCheck preambleLength
    | valueToCheck == total        = (True, take preambleLength keys)
    | length keys < preambleLength = (False, [])
    | otherwise                    = checkSums (tail keys) valueToCheck preambleLength
  where
    total = sum $ take preambleLength keys

main :: IO()
main = do
    keys <- readContent
    let answer1 = head $ checker keys [] 25
    let results = map snd $ filter fst $ map (checkSums keys answer1) [2 .. (length keys)]
    let answer2 = maximum (head results) + minimum (head results)
    print $ show answer1 ++ " " ++ show answer2