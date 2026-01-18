{-# LANGUAGE OverloadedStrings #-}

import Data.List
import qualified Data.Map as Map
import qualified Data.Text as T
import Control.Lens

convertToInt :: T.Text -> Int
convertToInt txt = (read $T.unpack txt) :: Int

getCount :: T.Text -> [(Char, Int)]
getCount str = map (\x -> (head x, length x)) $ group $ sort $ T.unpack str

unpackInput :: String -> [[T.Text]]
unpackInput str = map (T.splitOn " ") $ map T.pack $ lines str

checkPassword :: [T.Text] -> Int
checkPassword lst = 1 * checkMax * checkMin
   where
      minMaxRange = T.splitOn "-" $ head lst
      maxCount = convertToInt . last $ minMaxRange
      minCount = convertToInt . head $ minMaxRange
      mustHaveChar = head . T.unpack . head $ tail lst
      mappedChar = getCount $ last lst
      checkMax = 
          if ((> maxCount) <$> lookup mustHaveChar (mappedChar)) /= Just False
          then 0
          else 1
      checkMin =
          if ((< minCount) <$> lookup mustHaveChar (mappedChar)) /= Just False
          then 0
          else 1

checkPassword2 :: [T.Text] -> Int
checkPassword2 lst = (*) 1 $ abs (checkMax-checkMin)
   where 
       minMaxRange = T.splitOn "-" $ head lst
       maxCount = convertToInt . last $ minMaxRange
       minCount = convertToInt . head $ minMaxRange
       mustHaveChar = head . T.unpack . head $ tail lst
       checkMax = 
           if ((T.unpack $ last lst) ^? element (maxCount - 1)) /= Just mustHaveChar
           then 1
           else 0
       checkMin = 
           if ((T.unpack $ last lst) ^? element (minCount - 1)) /= Just mustHaveChar
           then 1
           else 0

recursionOverInput :: [[T.Text]] -> Int
recursionOverInput [] = 0
recursionOverInput (x:xs) = check + recursionOverInput xs
     where check = checkPassword2 x

main :: IO ()
main = do
    ls <- readFile "input.txt"
    let unpackedLs = unpackInput ls
    print $ recursionOverInput unpackedLs