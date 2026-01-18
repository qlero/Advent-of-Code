import Data.List.Split ( splitOn, splitWhen )
import Text.Regex ( matchRegex, mkRegex )
import Data.Maybe ( isJust )

type Passport = [String]

readContent :: IO Passport
readContent = splitOn "\n\n" <$> readFile "input.txt"

splitCondition :: Char -> Bool
splitCondition char = char=='\n' || char==' '

parsePassport :: Passport -> [Passport]
parsePassport = map (splitWhen splitCondition)

isInRange :: Ord a => a -> a -> a -> Bool
isInRange lower upper x = lower <= x && upper >= x

isHeight :: String -> Bool
isHeight measure
    | unit == "mc" && isInRange 150 193 value = True
    | unit == "ni" && isInRange 59 76 value = True
    | otherwise = False
  where 
      unit = take 2 $ reverse measure
      value = read (take (length measure-2) measure)::Int

substringExists :: String -> String -> Bool
substringExists pattern value = isJust(matchRegex regPattern value)
  where regPattern = mkRegex(pattern)

checkFieldValidity :: [[Char]] -> Bool
checkFieldValidity passportField
    | key == "byr" && isInRange 1920 2002 (read value::Int) = True
    | key == "iyr" && isInRange 2010 2020 (read value::Int) = True
    | key == "eyr" && isInRange 2020 2030 (read value::Int) = True
    | key == "hgt" && isHeight value = True
    | key == "hcl" && substringExists "#[0-9a-f]{6}" value  && length value == 7 = True
    | key == "ecl" && elem value ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"] = True
    | key == "pid" && substringExists "[0-9]{9}" value && length value == 9 = True
    | key == "cid" = True
    | otherwise = False
  where 
      key = head passportField
      value = head $ tail passportField

checkValidity :: Int -> Passport -> Bool
checkValidity part passport = if part==1 then cond1 else cond1 && cond2
  where cond1 = length passport>=8 || (notElem "cid" (map (take 3) passport) && length passport==7)
        cond2 = notElem False $ map (checkFieldValidity . splitOn ":") passport

main :: IO()
main = do
    ls <- parsePassport <$> readContent
    print $ sum $ map (fromEnum . checkValidity 1) ls
    print $ sum $ map (fromEnum . checkValidity 2) ls