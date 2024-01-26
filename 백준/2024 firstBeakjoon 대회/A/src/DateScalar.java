import graphql.schema.*;
import graphql.language.StringValue;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.function.Function;

public class DateScalar {
    public static final GraphQLScalarType DATE = GraphQLScalarType.newScalar()
            .name("Date")
            .description("Date custom scalar type")
            .coercing(new Coercing<LocalDate, String>() {
                @Override
                public String serialize(Object dataFetcherResult) {
                    if (dataFetcherResult instanceof LocalDate) {
                        return ((LocalDate) dataFetcherResult).format(DateTimeFormatter.ISO_LOCAL_DATE);
                    }
                    throw new CoercingSerializeException("Expected a LocalDate object.");
                }

                @Override
                public LocalDate parseValue(Object input) {
                    if (input instanceof String) {
                        return LocalDate.parse((String) input, DateTimeFormatter.ISO_LOCAL_DATE);
                    }
                    throw new CoercingParseValueException("Expected a String");
                }

                @Override
                public LocalDate parseLiteral(Object input) {
                    if (input instanceof StringValue) {
                        return LocalDate.parse(((StringValue) input).getValue(), DateTimeFormatter.ISO_LOCAL_DATE);
                    }
                    throw new CoercingParseLiteralException("Expected a StringValue.");
                }
            })
            .build();
}
