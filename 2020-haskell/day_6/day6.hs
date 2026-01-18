import Data.List.Split ( splitOn, splitWhen )
import Data.List.Utils ( replace )
import Data.List ( nub, intersect )

readContent :: IO [String]
readContent = splitOn "\n\n" <$> readFile "input.txt"

splitCondition :: Char -> Bool
splitCondition char = char=='\n'

parseGroupAnswers :: [String] -> [[String]]
parseGroupAnswers = map (splitWhen splitCondition)

countAnsweredQuestions :: [String] -> Int
countAnsweredQuestions = sum . map (length . nub)

intersectingAnswers :: [String] -> [String]
intersectingAnswers groupAnswers 
  | length groupAnswers == 1 = groupAnswers
  | otherwise = [foldl intersect front $ intersectingAnswers end]
  where
      front = head groupAnswers 
      end = tail groupAnswers

countIntersectingAnswers :: [[String]] -> Int
countIntersectingAnswers answers = sum $ map (sum . fmap length) commonAnswers
  where
      commonAnswers = map intersectingAnswers answers

main :: IO()
main = do
    surveys <- readContent
    print $ countAnsweredQuestions $ map (replace "\n" "") surveys
    print $ countIntersectingAnswers $ parseGroupAnswers surveys
